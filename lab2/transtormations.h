#pragma once
#include <glm/glm.hpp>

namespace mt
{
	inline glm::mat4 genRotationMatrix(glm::vec3 vec);



	
	inline float length(const glm::vec3& vec)
	{
		return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	inline glm::vec3 normalize(const glm::vec3& vec)
	{
		const float lenght = length(vec);
		return glm::vec3(vec[0] / lenght, vec[1] / lenght, vec[2] / lenght);
	}

	inline glm::mat4 scale(const glm::mat4& matrix, const glm::vec3& scale)
	{
		glm::mat4 result(matrix);
		result[0][0] = matrix[0][0] * scale[0];
		result[1][1] = matrix[1][1] * scale[1];
		result[2][2] = matrix[2][2] * scale[2];
		result[3][3] = matrix[3][3];
		return result;
	}

	inline glm::mat4 rotate(const glm::mat4& matrix, float angle, const glm::vec3& axes)
	{
		//float sine = sin(angle);
		//float cosine = cos(angle);

		//glm::mat4 rotation;
		//glm::vec3 R = normalize(axes);
		//glm::vec3 antiLock = R * (1.0f - cosine);

		//rotation[0][0] = cosine + antiLock.x * R.x;
		//rotation[0][1] = R.y * antiLock.x + R.z * sine;
		//rotation[0][2] = R.z * antiLock.x - R.y * sine;
		////rotation[0][3] = 0;
		//rotation[1][0] = R.x * antiLock.y - R.z * sine;
		//rotation[1][1] = cosine + R.y * antiLock.y;
		//rotation[1][2] = R.z * antiLock.y + R.x * sine;
		////rotation[1][3] = 0;
		//rotation[2][0] = R.x * antiLock.z + R.y * sine;
		//rotation[2][1] = R.y * antiLock.z - R.x * sine;
		//rotation[2][2] = cosine + R.z * antiLock.z;
		////rotation[2][3] = 0;

		//glm::mat4 result;
		//result[0] = matrix[0] * rotation[0][0] + matrix[1] * rotation[0][1] + matrix[2] * rotation[0][2];
		//result[1] = matrix[0] * rotation[1][0] + matrix[1] * rotation[1][1] + matrix[2] * rotation[1][2];
		//result[2] = matrix[0] * rotation[2][0] + matrix[1] * rotation[2][1] + matrix[2] * rotation[2][2];
		//result[3] = matrix[3];

		auto result = genRotationMatrix(axes * angle);
		return result * matrix;
	}

	inline glm::mat4 getTranslationMatrix(const glm::vec3 vec)
	{
		glm::mat4 res(1.0f);
		res[3][0] = vec[0];
		res[3][1] = vec[1];
		res[3][2] = vec[2];
		return res;
	}

	inline glm::mat4 translate(const glm::mat4& matrix, const glm::vec3& vec)
	{
		/*glm::mat4 result(matrix);
		result[3][0] = matrix[3][0] + vec.x;
		result[3][1] = matrix[3][1] + vec.y;
		result[3][2] = matrix[3][2] + vec.z;
		result[3][3] = matrix[3][3];*/
		
		/*glm::mat4 result(matrix);
		result[3] = matrix[0] * vec[0] + matrix[1] * vec[1] + matrix[2] * vec[2] + matrix[3];*/

		glm::mat4 result = getTranslationMatrix(vec);
		result = result * matrix;
		return result;
	}

	inline glm::mat4 translateTo(const glm::mat4& matrix, const glm::vec3& target)
	{
		glm::mat4 result(matrix);
		result[3][0] = target.x;
		result[3][1] = target.y;
		result[3][2] = target.z;
		result[3][3] = matrix[3][3];
		return result;
	}

	inline glm::mat4 reflectX(const glm::mat4& matrix)
	{
		glm::mat4 result(matrix);
		result[0][0] = -matrix[0][0];
		return result;
	}

	inline glm::mat4 reflectY(const glm::mat4& matrix)
	{
		glm::mat4 result(matrix);
		result[1][1] = -matrix[1][1];
		return result;
	}

	inline glm::mat4 reflectZ(const glm::mat4& matrix)
	{
		glm::mat4 result(matrix);
		result[2][2] = -matrix[2][2];
		return result;
	}

	inline glm::mat4 reflect(const glm::mat4& matrix, bool x, bool y, bool z)
	{
		glm::mat4 result(matrix);
		if (x)
			result = reflectX(result);
		if (y)
			result = reflectY(result);
		if (z)
			result = reflectZ(result);
		return result;
	}
	
	inline glm::mat4 genRotationMatrixX(float angle)
	{
		glm::mat4 res(1.0f);
		res[1][1] = cos(angle);
		res[1][2] = sin(angle);
		res[2][1] = -sin(angle);
		res[2][2] = cos(angle);
		return res;
	}

	inline glm::mat4 genRotationMatrixY(float angle)
	{
		glm::mat4 res(1.0f);
		res[0][0] = cos(angle);
		res[0][2] = -sin(angle);
		res[2][0] = sin(angle);
		res[2][2] = cos(angle);
		return res;
	}

	inline glm::mat4 genRotationMatrixZ(float angle)
	{
		glm::mat4 res(1.0f);
		res[0][0] = cos(angle);
		res[1][0] = -sin(angle);
		res[0][1] = sin(angle);
		res[1][1] = cos(angle);
		return res;
	}
	
	inline glm::mat4 genRotationMatrix(glm::vec3 vec)
	{
		auto Rx = genRotationMatrixX(vec.x);
		auto Ry = genRotationMatrixY(vec.y);
		auto Rz = genRotationMatrixZ(vec.z);
		return Rx * Ry * Rz;
	}

	
};




