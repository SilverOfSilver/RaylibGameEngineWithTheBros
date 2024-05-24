#include <raylib.h>
#include <math.h>

Vector3 MakeV3(float V1, float V2, float V3) {
	Vector3 retVec = { V1, V2, V3 };
	return retVec;
}
Vector3 AddV3(Vector3 V31, Vector3 V32) {
	Vector3 retVec = { V31.x + V32.x, V31.y + V32.y, V31.z + V32.z };
	return retVec;
}

Vector3 DirectionFromPitchYaw(float pitch, float yaw) {

	float sinPitch = sinf(pitch);
	float cosPitch = cosf(pitch);
	float sinYaw = sinf(yaw);
	float cosYaw = cosf(yaw);

	// Direction vector (normalized for length 1)
	Vector3 direction = { cosYaw * sinPitch, cosPitch, sinYaw * sinPitch };
	return direction;
}
Vector3 DirectionFromPitchYawScaled(float pitch, float yaw, float scale) {

	float sinPitch = sinf(pitch);
	float cosPitch = cosf(pitch);
	float sinYaw = sinf(yaw);
	float cosYaw = cosf(yaw);

	// Direction vector (normalized for length 1)
	Vector3 direction = { cosYaw * sinPitch * scale, cosPitch * scale, sinYaw * sinPitch * scale };
	return direction;
}

struct PhysObj //WIP
{
	bool colision;
	bool gravity;
	Vector3 loacation;
	Vector3 dir;
	double speed;
};

int main() {
	int screenWidth = 800;
	int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Testicle");

	Camera3D camera;
	camera.position = MakeV3(0, 0, 0); // Move camera slightly back
	camera.target = MakeV3(1, 0, 0);
	camera.up = MakeV3(0, 1, 0);
	camera.fovy = 60.0f; // Adjust field of view if needed
	camera.projection = CAMERA_PERSPECTIVE;
	float mouseDeltaX = GetMouseDelta().x;
	float mouseDeltaY = GetMouseDelta().y;
	float lookPitch = 0.5;
	float lookYaw = 0;
	float MoveX = 0;
	float MoveY = 0;
	HideCursor();

	Model TestModel = LoadModel("Models/blood_gulch.glb");
	Model SphereModel = LoadModel("Models/sphere.glb");


	while (!WindowShouldClose()) {

		mouseDeltaX = GetMouseDelta().x;
		mouseDeltaY = GetMouseDelta().y;
		SetMousePosition(screenWidth / 2, screenHeight / 2);

		// Adjust rotation speed based on your preference (e.g., 0.01f)
		float rotationSpeed = 0.001;
		lookPitch += mouseDeltaY * rotationSpeed;
		lookPitch = (lookPitch > 3.14159) ? 3.14159 : (lookPitch < 0) ? 0 : lookPitch;
		lookYaw += mouseDeltaX * rotationSpeed;
		camera.target = AddV3(camera.position, DirectionFromPitchYaw(lookPitch, lookYaw));

		if (IsKeyDown(KEY_W))
		{
			camera.position = AddV3(camera.position, DirectionFromPitchYawScaled(lookPitch, lookYaw, 0.001));
		}
		if (IsKeyDown(KEY_S))
		{
			camera.position = AddV3(camera.position, DirectionFromPitchYawScaled(lookPitch, lookYaw, -0.001));
		}
		if (IsKeyDown(KEY_A))
		{
			camera.position = AddV3(camera.position, DirectionFromPitchYawScaled((3.14159 / 2), lookYaw + (3.14159 / 2), -0.001));
		}
		if (IsKeyDown(KEY_D))
		{
			camera.position = AddV3(camera.position, DirectionFromPitchYawScaled((3.14159 / 2), lookYaw + (3.14159 / 2), 0.001));
		}
		if (IsKeyDown(KEY_SPACE))
		{
			camera.position = AddV3(camera.position, MakeV3(0, 0.001, 0));
		}
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			camera.position = AddV3(camera.position, MakeV3(0, -0.001, 0));
		}





		BeginDrawing();

		// Clear the screen with black background
		ClearBackground(SKYBLUE);
		BeginMode3D(camera);

		DrawModel(TestModel, MakeV3(0, 1, 0), 1, GRAY);
		DrawModel(SphereModel, MakeV3(5, 1, 0), 1, RED);



		EndMode3D();

		DrawFPS(10, 10);

		EndDrawing();


	}

	CloseWindow();
	return 0;
}