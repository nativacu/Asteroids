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

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
		, asteroid_count_(5)
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		ship_ = new Player();

		for (int i = 0; i < asteroid_count_; i++) {
			asteroids_.push_back(Asteroid());
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
			if (asteroid_count_ < 20) {
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

		case SDL_SCANCODE_SPACE:
			//if (bullets_.size() < 6) {
				bullets_.push_back(Bullet(*ship_));
			//}
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

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		//double elapsedTime = endTime - startTime;        

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		m_nUpdates++;

		
		for (int i = 0; i < asteroids_.size(); i++) {
			ship_->IsColliding(asteroids_[i]);
			if (ship_->GetIsColliding() && !ship_->GetIsDebugging()) {
				ship_->SetIsAlive(false);
			}
			asteroids_[i].Update(DESIRED_FRAME_TIME);
		}
		ShootAsteroids();

		ship_->Update(DESIRED_FRAME_TIME);

		for (int i = 0; i < bullets_.size(); i++) {
			bullets_[i].Update(DESIRED_FRAME_TIME);
		}

	}

	void App::Render()
	{
		ColorScheme cs;
		glClear(GL_COLOR_BUFFER_BIT);
		cs.change_background(cs.green);
		
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
					asteroids_[i].SetWasShot(true);
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

	/*
	void App::ShootAsteroids()
	{
		bool ifCollision = false;
		for (int i = 0; i < asteroids_.size(); i++)
		{
			Vector2 asteroid_position = asteroids_[i].GetPosition();
	
			for (int j = 0; j < bullets_.size(); j++)
			{
				Vector2 bullet_position = bullets_[j].GetPosition();

				float distanceToAsteroid = asteroids_[i].GetEntitiesDistance(bullets_[j]);

				if (distanceToAsteroid <= (bullets_[j].GetRadius() + asteroids_[i].GetRadius()))
				{
					if (asteroids_[i].GetSize() == 3)
					{
						asteroids_.push_back(Asteroid(2));
						asteroids_.push_back(Asteroid(2));
						asteroids_.erase(asteroids_.begin() + i);
						bullets_.erase(bullets_.begin() + j);
						ifCollision = true;
					}
					else if (asteroids_[i].GetSize() == 2)
					{
						asteroids_.push_back(Asteroid(1));
						asteroids_.push_back(Asteroid(1));
						asteroids_.erase(asteroids_.begin() + i);
						bullets_.erase(bullets_.begin() + j);
						ifCollision = true;;
					}
					else
					{
						asteroids_.erase(asteroids_.begin() + i);
						bullets_.erase(bullets_.begin() + j);
						ifCollision = true;
					}
				}
				break;
			}
			if (ifCollision)
				break;
		}
	}

	*/
	void App::ShootAsteroids()
	{
		bool is_asteroid_deleted = false;

		int next_size = 0;
		for (int i = 0; i < asteroids_.size(); i++)
		{
			for (int j = 0; j < bullets_.size(); j++)
			{
				asteroids_[i].WasShot(bullets_[j]);
				if (asteroids_[i].GetWasShot()) {
					bullets_.pop_back();
					asteroids_.erase(asteroids_.begin() + i);
					asteroid_count_--;
					std::cout << "test" << std::endl;
					is_asteroid_deleted = true;
					if (asteroids_[i].GetSize() == 3){
						asteroids_.push_back(Asteroid(2));
						asteroids_.push_back(Asteroid(2));
						asteroid_count_ += 2;
					}

					else if (asteroids_[i].GetSize() == 2)
					{
						asteroids_.push_back(Asteroid(1));
						asteroids_.push_back(Asteroid(1));
						asteroid_count_ += 2;
					}

				}
				break;
			}

			if (is_asteroid_deleted) break;
		}
	}
	
	
}
