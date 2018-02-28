#include "App.hpp"
#include <iostream>
#include <algorithm>
#include <time.h>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

//New includes
#include "ColorScheme.h"
#include "Bullet.hpp"



namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
	const float kGraphXAxisPosition = 300.0f;
	const float kGraphYAxisPosition = -300.0f;
	const float kLifeDisplayXAxisPosition = 36;
	const float kLifeDisplayYAxisPosition = 40;
	const float kShipDifference = 3;
	const int kInmortalitySeconds = 2;
	const int kMaxFrameCount = 10;
	const int kMaxLives = 3;
	const int kMaxBullets = 6;
	const int kMaxAsteroids = 20;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
		, asteroid_count_(5)
		, life_counter_(3)
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		graph_ = false;
		ship_ = new Player();

		for (int i = 0; i < asteroid_count_; i++) {
			asteroids_.push_back(Asteroid());
		}

		delta_time_ = DESIRED_FRAME_TIME;

		current_frame_position_ = 0;
		capt_frames_ = std::vector<Vector2>(kMaxFrameCount);

		for (int i = 0; i < capt_frames_.size(); i++)
		{
			capt_frames_[i] = Vector2((static_cast <float>(i), DESIRED_FRAME_TIME));
		}
	}

	App::~App()
	{
		CleanupSDL();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;
	
		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			ship_->SetIsMovingUp(true);
			ship_->MoveForward();
			break;

		case SDL_SCANCODE_RIGHT:
			ship_->SetIsMovingRight(true);
			break;

		case SDL_SCANCODE_LEFT:
			ship_->SetIsMovingLeft(true);
			break;

		case SDL_SCANCODE_M:
			
			if (asteroid_count_ < kMaxAsteroids) {
				asteroid_count_++;
				asteroids_.push_back(Asteroid());
			}
			break;

		case SDL_SCANCODE_L:
			if (asteroid_count_ > 0) {
				asteroid_count_--;
				asteroids_.pop_back();
			}
			break;

		case SDL_SCANCODE_D:
			if (ship_->GetIsAlive()) {
				ship_->SetIsDebugging();
				for (int i = 0; i < asteroids_.size(); i++) {
					asteroids_[i].SetIsDebugging();
				}
			}
			break;

		case SDL_SCANCODE_F:
			if (graph_) {
				graph_ = false;
			}
			else {
				graph_ = true;
			}
			break;

		case SDL_SCANCODE_R:
			if (life_counter_ > 0 && !ship_->GetIsAlive()) {
				ship_->SetRespawned(true);
				life_counter_--;
				respawn_timer_ = m_timer->GetElapsedTimeInSeconds();
			}
			break;

		case SDL_SCANCODE_SPACE:
			if (bullets_.size() < kMaxBullets && ship_->GetIsAlive() && !ship_->GetRespawned()) {
				bullets_.push_back(Bullet(*ship_));
			}
			break;

		default:
			SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
			SDL_Log("%d",asteroids_.size());
			break;
		}
	}
	
	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			ship_->SetIsMovingUp(false);
			ship_->SetIsMovingRight(false);
			ship_->SetIsMovingLeft(false);
			break;

		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;

		default:
			//DO NOTHING
			break;
		}
	}
	

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();
		// Update code goes here
		//

		for (int i = 0; i < asteroids_.size(); i++) {
			ship_->IsColliding(asteroids_[i]);
			if (ship_->GetIsColliding() && !ship_->GetIsDebugging()) {
				ship_->SetIsAlive(false);
			}
			asteroids_[i].Update(delta_time_);
		}

		for (int i = 0; i < bullets_.size(); i++) {
			bullets_[i].Update(delta_time_);
		}

		ship_->Update(delta_time_);

		ShootAsteroids();

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		delta_time_ = DESIRED_FRAME_TIME - (endTime - startTime);
		UpdateFrameSequence();

		while (endTime < nextTimeFrame){
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		//double elapsedTime = endTime - startTime;   
		if (ship_->GetRespawned()) {
			int a = 0;
			if (endTime - respawn_timer_ < kInmortalitySeconds) {
				ship_->SetIsColliding(false);
				if (ship_->GetIsAlive() && a > 50) {
					ship_->SetIsAlive(false);
					a=0;
				}
				else {
					ship_->SetIsAlive(true);
					a++;
				}
			}
			else {
				ship_->SetIsAlive(true);
				ship_->SetRespawned(false);
			}
		}

		if (asteroid_count_ < 5) {
			asteroids_.push_back(Asteroid());
			asteroid_count_++;
		}

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		m_nUpdates++;
	}

	void App::Render(){
		ColorScheme cs;
		glClear(GL_COLOR_BUFFER_BIT);
		cs.change_background(cs.green);
		
		DisplayLives();

		if (ship_->GetIsAlive() || ship_->GetIsDebugging()) {
			ship_->Render();
			for (int i = 0; i < bullets_.size(); i++) {
				if (bullets_[i].GetIsAlive()) {
					bullets_[i].Render();
				}
				else {
					bullets_.erase(bullets_.begin() + i);
				}
			}
		}
		
		for (int i = 0; i < asteroids_.size(); i++) {
			asteroids_[i].Render();
		}

		if (ship_->GetIsDebugging()) {
			ship_->SetIsColliding(false);
			for (int i = 0; i < asteroids_.size(); i++) {
				asteroids_[i].SetIsColliding(false);
			}
			DrawDebugLines();
			DrawDebugBulletLines();
		}

		if (ship_->GetRespawned()) {
		//	ship_->DrawCircle();
		}

		if (graph_) {
			GetFrameRate();
		}
		
		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags = SDL_WINDOW_OPENGL |
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;


		ship_->SetWindowDimensions(width, height);
		for (int i = 0; i < asteroid_count_; i++) {
			asteroids_[i].SetWindowDimensions(width, height);
		}

		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}

	void App::DrawDebugLines() {
		ColorScheme color;
		
		glLoadIdentity();
		float proximity_measurement = 2 * ship_->GetRadius();
		Vector2 ship_position = ship_->GetPosition();
		int j = 0;

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < asteroids_.size(); i++) {
			float distance = ship_->GetEntitiesDistance(asteroids_[i]);
			Vector2 asteroid_position = asteroids_[i].GetPosition();
			float added_radius = proximity_measurement + asteroids_[i].GetRadius();

			if (distance <= added_radius) {
				asteroids_[i].SetIsColliding(true);
				ship_->SetIsColliding(true);
				glColor4f(color.red.red,color.red.green,color.red.blue,color.red.opacity);
				glVertex2f(ship_position.x, ship_position.y);
				glVertex2f(asteroid_position.x, asteroid_position.y);
			}
		}
		glEnd();

		ship_->SetIsColliding(false);
		
		glColor3f(1, 1, 1);
	}

	void App::DrawDebugBulletLines() {
		ColorScheme color;

		glLoadIdentity();

		glBegin(GL_LINE_LOOP);
		for (int k = 0; k < bullets_.size(); k++) {
			for (int i = 0; i < asteroids_.size(); i++) {
				float proximity_measurement = 2 * asteroids_[i].GetRadius();
				float distance = bullets_[k].GetEntitiesDistance(asteroids_[i]);
				Vector2 asteroid_position = asteroids_[i].GetPosition();
				Vector2 bullet_position = bullets_[k].GetPosition();
				float added_radius = bullets_[k].GetRadius() + proximity_measurement;

				if (distance <= added_radius) {
					glColor4f(color.yellow.red, color.yellow.green, color.yellow.blue, color.yellow.opacity);
					glVertex2f(bullet_position.x, bullet_position.y);
					glVertex2f(asteroid_position.x, asteroid_position.y);
				}
			}
		}
		glEnd();

		ship_->SetIsColliding(false);

		glColor3f(1, 1, 1);
	}

	void App::GetFrameRate(){
		glLoadIdentity();
		glTranslatef(kGraphXAxisPosition, kGraphYAxisPosition, 0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(0.0f, 100.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(130.0f, 0.0f);
		glEnd();

		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < kMaxFrameCount; i++)
		{
			glVertex2f(10.0f * capt_frames_[i].x, 100000.0f * (DESIRED_FRAME_TIME - capt_frames_[i].y));
		}
		glEnd();
	}

	void App::ShootAsteroids(){
		bool is_asteroid_deleted = false;
		for (int i = 0; i < asteroids_.size(); i++){

			for (int j = 0; j < bullets_.size(); j++){
				asteroids_[i].WasShot(bullets_[j]);
				if (asteroids_[i].GetWasShot()) {
					Vector2 parent_position = asteroids_[i].GetPosition();
					bullets_.erase(bullets_.begin() + j);
					is_asteroid_deleted = true;

					if (asteroids_[i].GetSize() == 3){
						Asteroid fst_child_(2);
						Asteroid snd_child_(2);
						fst_child_.SetPosition(parent_position);
						snd_child_.SetPosition(parent_position+10);
						asteroids_.push_back(fst_child_);
						asteroids_.push_back(snd_child_);
						asteroid_count_ += 2;
					}

					else if (asteroids_[i].GetSize() == 2){
						Asteroid fst_child_(1);
						Asteroid snd_child_(1);
						fst_child_.SetPosition(parent_position);
						snd_child_.SetPosition(parent_position+10);
						asteroids_.push_back(fst_child_);
						asteroids_.push_back(snd_child_);
						asteroid_count_ += 2;
					}

					asteroids_.erase(asteroids_.begin() + i);
					asteroid_count_--;
					break;
				}
			}

			if (is_asteroid_deleted) break;
		}
	}

	void App::UpdateFrameSequence(void){
		capt_frames_[current_frame_position_] = Vector2((float)current_frame_position_, delta_time_);
		current_frame_position_++;

		if (current_frame_position_ >= kMaxFrameCount) {
			current_frame_position_ = 0;
		}
	}

	void App::DisplayLives() {
		float life_factor = 1;
		
		for (int i = 0; i < life_counter_; i++) {
			float x_axis = m_width / 2 - kLifeDisplayXAxisPosition * life_factor;
			float y_axis = m_height / 2 - kLifeDisplayYAxisPosition;
			std::vector<Vector2> ship_vertices = ship_->GetVertices();
			glLoadIdentity();
			glTranslatef(x_axis, y_axis, 0.0f);

			glBegin(GL_LINE_LOOP);

			for (int j = 0; j < ship_vertices.size(); j++) {
				glVertex2f(ship_vertices[j].x/kShipDifference, ship_vertices[j].y/kShipDifference);
			}

			glEnd();
			life_factor++;
		}
	}

}


