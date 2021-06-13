/* \file RenderComponent.h */

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	class TransformComponent
	{
	public:
		glm::vec3 translation = { 0.f, 0.f, 0.f };
		//glm::vec3 rotation = { 0.f, 0.f, 0.f }; // Should be changed to quaternion
		glm::vec3 scale = { 1.f, 1.f, 1.f };
		TransformComponent() { transform = glm::mat4(1.0f); }

		TransformComponent(glm::vec3 t, glm::vec3 r, glm::vec3 s)
		{
			setTransform(t, r, s);
		}

		glm::mat4& setTransform(glm::vec3 t, glm::quat r, glm::vec3 s)
		{
			translation = t;
			rotation = r;
			scale = s;

			return updateTransform();
		}

		glm::mat4& setTransform(glm::vec3 t, glm::vec3 r, glm::vec3 s)
		{
			translation = t;
			rotation = glm::quat(r);
			scale = s;

			return updateTransform();
		}

		glm::mat4& setTransform(glm::mat4& parentTransform, glm::vec3 t, glm::vec3 r, glm::vec3 s)
		{
			translation = t;
			rotation = glm::quat(r);
			scale = s;

			return updateTransform(parentTransform);
		}

		glm::mat4& updateTransform()
		{
			/*glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.f,0.f,0.f });
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), rotation.y, { 0.f,1.f,0.f });
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), rotation.z, { 0.f,0.f,1.f });
			glm::mat4 rot = rotX * rotY * rotZ;*/

			transform = glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);

			return transform;
		}

		glm::mat4& updateTransform(glm::mat4& parentTransform)
		{
			transform = parentTransform * updateTransform();

			return transform;
		}

		void addRotation(glm::vec3& eularAngles)
		{
			glm::quat rotationalDelta(eularAngles);
			rotation *= rotationalDelta;
		}

		glm::mat4& getTransform() { return transform; }
		glm::vec3 getTranslation() { return translation; }
		float getRotationX() { return rotation.x; }
		float getRotationY() { return rotation.y; }
		float getRotationZ() { return rotation.z; }

		glm::quat rotation;
	private:
		glm::mat4 transform;
	};
}


