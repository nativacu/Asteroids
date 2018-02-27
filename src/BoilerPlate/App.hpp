#pragma once
#ifndef APP_HPP
#define APP_HPP

// C++ STL
#include <string>
#include <list>

// Asteroids
#include "SDLEvent.hpp"
#include "TimeManager.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <vector>

namespace Engine
{
	class App : public SDLEvent
	{
	public:
		/* =============================================================
		* ENUMERATORS
		* ============================================================= */
		struct GameState
		{
			enum State
			{
				UNINITIALIZED = 0,
				INIT_FAILED = 1,
				INIT_SUCCESSFUL = 2,
				RUNNING = 4,
				PAUSED = 8,
				QUIT = 16
			};
		};

		/* =============================================================
		 * PUBLIC FUNCTIONS
		 * ============================================================= */
		App( const std::string& title, const int width, const int height );
		~App( );
		void Execute						( );
		bool Init							( );
		void Update							( );
		void DrawDebugLines					( );
		void DrawDebugBulletLines			( );
		void GetFrameRate					( );
		void UpdateFrameSequence			( );
		void ShootAsteroids					( );
		void Render							( );
	private:
		/* =============================================================
		 * PRIVATE FUNCTIONS
		 * ============================================================= */
		bool SDLInit						( );
		bool GlewInit						( );
		void SetupViewport					( );
		void CleanupSDL						( );
		void OnResize						( int width, int height ) override;
		void OnExit							( ) override;
		void OnKeyDown						( SDL_KeyboardEvent keyBoardEvent ) override;
		void OnKeyUp						( SDL_KeyboardEvent keyBoardEvent ) override;


		/* =============================================================
		 * MEMBERS
		 * ============================================================= */
		int										m_width;
		int										m_height;
		int										m_nUpdates;
		double									m_lastFrameTime;
		std::string								m_title;
		SDL_Window*								m_mainWindow;
		SDL_GLContext							m_context;
		GameState::State						m_state;
		Engine::TimeManager*					m_timer;
		std::vector<Asteroid>					asteroids_;
		Player*									ship_;
		int										asteroid_count_;
		std::vector<Bullet>						bullets_;
		int										current_frame_position_;
		std::vector<Vector2>					capt_frames_;
		float									delta_time_;
		bool									graph_;
		bool									showingPlot;
	};
}
#endif /* GAME_HPP */
