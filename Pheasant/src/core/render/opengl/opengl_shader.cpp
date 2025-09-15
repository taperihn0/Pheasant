#include "opengl_shader.h"
#include "opengl_backend.h"
#include "shaderc/shaderc.hpp"

namespace Phs
{

static constexpr bool PhsGlShaderSUCCESS = 1;
static constexpr bool PhsGlShaderFAILURE = 0;

GLStageObject::GLStageObject()
	: _gl_shader_stage(_UndefGlShaderNum)
   , _gl_shader_type(_UndefGlShaderStage)
   , _compiled(false)
{}

bool GLStageObject::compile(const char* path, const char* source_content, ShaderStage shader_type)
{
	GLenum gl_shader_stage = 0;

	switch (shader_type)
	{
		case SHADER_STAGE_VERTEX:
			gl_shader_stage = GL_VERTEX_SHADER;
			break;
		case SHADER_STAGE_TESS_CONTROL:
			gl_shader_stage = GL_TESS_CONTROL_SHADER;
			break;
		case SHADER_STAGE_TESS_EVALUATION:
			gl_shader_stage = GL_TESS_EVALUATION_SHADER;
			break;
		case SHADER_STAGE_GEOMETRY:
			gl_shader_stage = GL_GEOMETRY_SHADER;
			break;
		case SHADER_STAGE_FRAGMENT:
			gl_shader_stage = GL_FRAGMENT_SHADER;
			break;
		case SHADER_STAGE_UNDEF:
			PHS_CORE_LOG_ERROR("Undefined shader stage!");
			return PhsGlShaderFAILURE;
	}

	return compileSource(path, source_content, gl_shader_stage);
}

bool GLStageObject::close()
{
	if (!isCompiled())
	{
		PHS_CORE_LOG_ERROR("Trying to delete non-compiled shader object!");
		return PhsGlShaderFAILURE;
	}
	glDeleteShader(_gl_shader_stage);
	return PhsGlShaderSUCCESS;
}

bool GLStageObject::isCompiled() const
{
	return _compiled;
}

bool GLStageObject::attachTo(GLuint gl_shader_program) const
{
	if (!isCompiled())
	{
		PHS_CORE_LOG_ERROR("Trying to attach non-compiled shader object!");
		return PhsGlShaderFAILURE;
	}

	glAttachShader(gl_shader_program, _gl_shader_stage);
	GLenum status = glGetError();
	return status == GL_NO_ERROR;
}

bool GLStageObject::detach(GLuint gl_shader_program) const
{
	glDetachShader(gl_shader_program, _gl_shader_stage);
	GLenum status = glGetError();
	return status == GL_NO_ERROR;
}

bool GLStageObject::compileSource(const char* path, const char* source_content, GLenum gl_shader_type)
{
	_gl_shader_type = gl_shader_type;
	_gl_shader_stage = glCreateShader(_gl_shader_type);

	shaderc_shader_kind shaderc_kind;

	switch (_gl_shader_type)
	{
	case GL_VERTEX_SHADER:
		shaderc_kind = shaderc_vertex_shader;
		break;
	case GL_TESS_CONTROL_SHADER:
		shaderc_kind = shaderc_tess_control_shader;
		break;
	case GL_TESS_EVALUATION_SHADER:
		shaderc_kind = shaderc_tess_evaluation_shader;
		break;
	case GL_GEOMETRY_SHADER:
		shaderc_kind = shaderc_geometry_shader;
		break;
	case GL_FRAGMENT_SHADER:
		shaderc_kind = shaderc_fragment_shader;
		break;
	default: 
		PHS_CORE_LOG_ERROR("Invalid shader type");
		return PhsGlShaderFAILURE;
	}

	shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	options.SetOptimizationLevel(shaderc_optimization_level_performance);

	shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source_content,
																						  shaderc_kind, 
																						  path,
																						  options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		PHS_CORE_LOG_FATAL("Shader compilation failed!");
		PHS_CORE_LOG_FATAL("Compilation error: {}", result.GetErrorMessage());
		return PhsGlShaderFAILURE;
	}

	std::vector<uint32_t> spirv(result.cbegin(), result.cend());

	glShaderBinary(1, &_gl_shader_stage, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));

	GLenum status = glGetError();
	
	if (status != GL_NO_ERROR)
		return PhsGlShaderFAILURE;

	glSpecializeShader(_gl_shader_stage, "main", 0, nullptr, nullptr);

	if (status != GL_NO_ERROR)
		return PhsGlShaderFAILURE;

	GLint compiled_status = 0;
	glGetShaderiv(_gl_shader_stage, GL_COMPILE_STATUS, &compiled_status);

	if (compiled_status == GL_FALSE)
	{
		GLint max_size = 0;
		glGetShaderiv(_gl_shader_stage, GL_INFO_LOG_LENGTH, &max_size);

		std::string info;
		info.reserve(max_size);

		glGetShaderInfoLog(_gl_shader_stage, max_size, &max_size, info.data());

		glDeleteShader(_gl_shader_stage);

		PHS_CORE_LOG_FATAL("Shader specialization failed: {}", info);
		return PhsGlShaderFAILURE;
	}

	PHS_CORE_LOG_TRACE("Shader compiled successfully");
	
	_compiled = true;	
	return PhsGlShaderSUCCESS;
}

GLShader::GLShader()
	: _shader_stages{}
	, _linked(false)
{
	_gl_shader_program = glCreateProgram();
}

GLShader::~GLShader()
{
	close();
	glDeleteProgram(_gl_shader_program);
}

bool GLShader::close()
{
	for (uint i = 0; i < ShaderStageCount; i++)
	{
		if (_shader_stages[i].isCompiled())
		{
			bool status = _shader_stages[i].close();
			if (!status) return PhsGlShaderFAILURE;

			if (_linked) 
			{
				status = _shader_stages[i].detach(_gl_shader_program);
				if (!status) return PhsGlShaderFAILURE;
			}
		}
	}

	_linked = false;
	return PhsGlShaderSUCCESS;
}

bool GLShader::compileAttachStage(const char* source_path, const char* source, ShaderStage stage)
{
	return _shader_stages[stage].compile(source_path, source, stage);
}

bool GLShader::linkProgram()
{
	for (uint i = 0; i < ShaderStageCount; i++)
	{
		if (_shader_stages[i].isCompiled())
		{
			bool status = _shader_stages[i].attachTo(_gl_shader_program);
			if (!status) return PhsGlShaderFAILURE;
		}
	}

	_linked = true;
	return PhsGlShaderSUCCESS;
}

bool GLShader::bind()
{
	if (!_linked)
	{
		PHS_CORE_LOG_ERROR("Trying to bind unliked shader program!");
		return PhsGlShaderFAILURE;
	}

	glUseProgram(_gl_shader_program);
	GLenum status = glGetError();
	return status == GL_NO_ERROR;
}

} // namespace Phs
