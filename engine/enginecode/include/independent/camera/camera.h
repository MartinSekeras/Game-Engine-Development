/** \file camera.h */
#pragma once
#include "renderer/rendererCommons.h"
#include "events/windowEvents.h"
#include "components/transform.h"

namespace Engine
{
	/** \class Camera
	*	\brief Class to create the camera, its view and projection, plus updating the view with transform.
	*/
	class Camera
	{
	public:
		glm::mat4 view;									//!< mat4 for the camera view.
		glm::mat4 projection;							//!< mat4 for the camera projection.
		void updateView(const glm::mat4& transform)
		{
			view = glm::inverse(transform);
		}			//!< update the view, taking the transform of the object, inverting the view based on this transform.

	private:
	};

	/** \class CameraController
	*	\brief Class to control the camera with events and inputs.
	*/
	class CameraController 
	{
	public:
		virtual inline Camera& getCamera() = 0;			//!< accessor for the camera.
		virtual void onUpdate(float time) = 0;			//!< update function taking time.
		virtual void onUpdate(float time, TransformComponent transformToFollow) = 0;			//!< on update function.
		virtual void onEvent(Event& event) = 0;			//!< event function taking events for camera manipulation.
		virtual void onResize(WindowResizeEvent& event) = 0; //!< Adjust camera on window resize
		Camera m_camera;								//!< the camera.
	protected:
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };	//!< vec3 to take position of camera.
	};
}