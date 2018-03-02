#include "InputManager.hpp"
InputManager* InputManager::instance = 0; //0 Because it will be initialized on demand

InputManager::InputManager(){
	was_up_key_pressed_ = false;
	was_left_key_pressed_ = false;
	was_right_key_pressed_ = false;
	was_space_key_pressed_ =  false;
	was_d_key_pressed_ = false;
	was_f_key_pressed_ = false;
	was_m_key_pressed_ = false;
	was_l_key_pressed_ = false;
	was_r_key_pressed_ = false;
}

InputManager::~InputManager()
{
}

//Singleton initializer
InputManager* InputManager::GetInstance() {
	if (instance == 0) {
		instance = new InputManager();
	}

	return instance;
}

void InputManager::SetWasUpKeyPressed(bool was_pressed) {
	was_up_key_pressed_ = was_pressed;
}

void InputManager::SetWasRightKeyPressed(bool was_pressed) {
	was_right_key_pressed_ = was_pressed;
}

void InputManager::SetWasLeftKeyPressed(bool was_pressed) {
	was_left_key_pressed_ = was_pressed;
}

void InputManager::SetWasSpaceKeyPressed(bool was_pressed) {
	was_space_key_pressed_ = was_pressed;
}

void InputManager::SetWasDKeyPressed(bool was_pressed) {
	was_d_key_pressed_ = was_pressed;
}

void InputManager::SetWasFKeyPressed(bool was_pressed) {
	was_f_key_pressed_ = was_pressed;
}

void InputManager::SetWasMKeyPressed(bool was_pressed) {
	was_m_key_pressed_ = was_pressed;
}

void InputManager::SetWasLKeyPressed(bool was_pressed) {
	was_l_key_pressed_ = was_pressed;
}

void InputManager::SetWasRKeyPressed(bool was_pressed){
	was_r_key_pressed_ = was_pressed;
}

bool InputManager::GetWasUpKeyPressed(void){
	return was_up_key_pressed_;
}

bool InputManager::GetWasRightKeyPressed(void) {
	return was_right_key_pressed_;
}

bool InputManager::GetWasLeftKeyPressed(void) {
	return was_left_key_pressed_;
}

bool InputManager::GetWasSpaceKeyPressed(void) {
	return was_space_key_pressed_;
}

bool InputManager::GetWasDKeyPressed(void) {
	return was_d_key_pressed_;
}

bool InputManager::GetWasFKeyPressed(void) {
	return was_f_key_pressed_;
}

bool InputManager::GetWasMKeyPressed(void) {
	return was_m_key_pressed_;
}

bool InputManager::GetWasLKeyPressed(void) {
	return was_l_key_pressed_;
}

bool InputManager::GetWasRKeyPressed(void){
	return was_r_key_pressed_;
}


