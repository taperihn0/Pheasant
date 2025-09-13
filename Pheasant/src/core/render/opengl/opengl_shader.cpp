#include "opengl_shader.h"
#include "shaderc/shaderc.hpp"

namespace Phs
{

static constexpr bool PhsGlShaderSUCCESS = 1;
static constexpr bool PhsGlShaderFAILURE = 0;

GLStageObject::GLStageObject()
   : _path(UndefFilePath)
	, _gl_shader_stage(_UndefGlShaderNum)
   , _gl_shader_type(_UndefGlShaderStage)
   , _compiled(false)
{}

GLStageObject::GLStageObject(std::string_view path, ShaderStage shader_type)
   : _path(path)
	, _gl_shader_stage(_UndefGlShaderNum)
   , _gl_shader_type(_UndefGlShaderStage)
   , _compiled(false)
{
   compile(path, shader_type);
}

bool GLStageObject::compile(std::string_view path, ShaderStage shader_type)
{
	File_Read file(path, FILE_MODE_BINARY);

	std::unique_ptr<FileToken> source_content;
	size_t source_size;

	if (!file.read(source_content, source_size))
	{
		PHS_CORE_LOG_ERROR("Failed to read from a file: {}", path);
		return PhsGlShaderFAILURE;
	}

	PHS_CORE_LOG_TRACE("Shader compilation:");
	PHS_CORE_LOG_TRACE("\nfile {}", _path);

	_path.assign(path);
	const char* cstr_content = reinterpret_cast<const char*>(source_content.get());

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

	return compileSource(cstr_content, shader_type);
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

bool GLStageObject::compileSource(const char* source_content, GLenum gl_shader_type)
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
																						  _path.c_str(),
																						  options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		PHS_CORE_LOG_FATAL("Shader compilation failed: {}", result.GetErrorMessage());
		return PhsGlShaderFAILURE;
	}

	std::vector<unsigned char> spirv(result.cbegin(), result.cend());

	glShaderBinary(1, &_gl_shader_stage, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size());
	glSpecializeShader(_gl_shader_stage, "main", 0, nullptr, nullptr);

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
	for (uint i = 0; i < _ShaderStageCount; i++)
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

bool GLShader::specifyStage(std::string_view path, ShaderStage stage)
{
	return _shader_stages[stage].compile(path, stage);
}

bool GLShader::linkProgram()
{
	for (uint i = 0; i < _ShaderStageCount; i++)
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

} // namespace Phs
