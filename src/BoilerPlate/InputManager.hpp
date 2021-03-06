#pragma once
class InputManager
{
private:
	static InputManager* instance;
	bool was_up_key_pressed_;
	bool was_right_key_pressed_;
	bool was_left_key_pressed_;
	bool was_space_key_pressed_;
	bool was_d_key_pressed_;
	bool was_f_key_pressed_;
	bool was_m_key_pressed_;
	bool was_l_key_pressed_;
	bool was_r_key_pressed_;
	InputManager();

public:
	~InputManager();
	//Singleton
	static InputManager* GetInstance();

	//Setters
	void SetWasUpKeyPressed(bool);
	void SetWasRightKeyPressed(bool);
	void SetWasLeftKeyPressed(bool);
	void SetWasSpaceKeyPressed(bool);
	void SetWasDKeyPressed(bool);
	void SetWasFKeyPressed(bool);
	void SetWasMKeyPressed(bool);
	void SetWasLKeyPressed(bool);
	void SetWasRKeyPressed(bool);

	//Getters
	bool GetWasUpKeyPressed(void);
	bool GetWasRightKeyPressed(void);
	bool GetWasLeftKeyPressed(void);
	bool GetWasSpaceKeyPressed(void);
	bool GetWasDKeyPressed(void);
	bool GetWasFKeyPressed(void);
	bool GetWasMKeyPressed(void);
	bool GetWasLKeyPressed(void);
	bool GetWasRKeyPressed(void);
};

