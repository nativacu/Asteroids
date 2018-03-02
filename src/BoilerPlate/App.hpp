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
#include <irrklang.h>
#include <vector>
#include "FontManager.hpp"
#include "InputManager.hpp"
//#include "Font.cpp"

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
		void ManageInput					( );
		void DrawDebugLines					( );
		void DrawDebugBulletLines			( );
		void GetFrameRate					( );
		void BreakAsteroid					(int, Vector2);
		void AddAsteroids					(int);
		void UpdateFrameSequence			( );
		void ShootAsteroids					( );
		void DisplayLives                   ( );
		void Render							( );
		void RestartGame					( );
		void SetFontColor					(int,int,int,int);
		void ScoreRender					();
		void GameOverRender					( );

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
		int										width_;
		int										height_;
		int										n_updates_;	
		double									last_frame_time;
		std::string								title_;
		SDL_Window*								main_window_;
		SDL_GLContext							context_;
		GameState::State						state_;
		Engine::TimeManager*					timer_;
		std::vector<Asteroid>					asteroids_;
		Player*									ship_;
		int										asteroid_count_;
		std::vector<Bullet>						bullets_;
		int										current_frame_position_;
		std::vector<Vector2>					capt_frames_;
		float									delta_time_;
		bool									graph_;
		int										life_counter_;
		double									respawn_timer_;
		int										respawn_blink_timer_;
		InputManager*							input_manager_;
		int										allowed_consecutive_key_input_;
		int										player_score_;
		int										points_to_extra_life_;
		irrklang::ISoundEngine*					sound_engine_;
		bool									played_game_over_sound_;
		FontManager*							font_manager_;
		TTF_Font*								font_;
		SDL_Color								font_color_;
		bool									game_over_;
	};
}
#endif /* GAME_HPP */
