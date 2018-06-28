// -------------------------------------------- //
// ---------- // Работа с камерой // ---------- //
// -------------------------------------------- //

#ifndef ME_CAMERA
#define ME_CAMERA

#include "ME_Main.h"
#include "ME_Input.h"

namespace ME {
	class Camera
	{
	public:
		Camera();
		Camera(vec3 position, vec3 targetPoint, vec3 axeVertical, float sensitivity, float speed);
		~Camera();

		void direct(int xRel, int yRel);
		void move(ME::Input const &input);
		void lookAt(mat4 &modelview);

		void setTargetPoint(vec3 targetPoint);
		void setPosition(vec3 position);

		float getSensitivity() const;
		float getSpeed() const;

		void setSensitivity(float sensitivity);
		void setSpeed(float speed);

	private:

		float m_phi, m_theta;
		vec3 m_orientation, m_axeVertical, m_deplacementLateral;
		vec3 m_position, m_targetPoint;

		float m_sensitivity, m_speed;
	};
}

#endif //- ME_CAMERA

// -------------------------------------------- //