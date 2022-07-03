//#pragma once
//#include "Sound_System.h"
//
//class ServiceLocater
//{
//	static Sound_System* _ss_instance;
//	static Null_Sound_System _default_ss;
//public:
//	static Sound_System& Get_Sound_System() { return *_ss_instance; }
//	static void Register_Sound_System(Sound_System* ss){ 
//		_ss_instance = ss == nullptr ? &_default_ss : ss;
//	}
//
//};
//Null_Sound_System ServiceLocater::_default_ss;
//Sound_System* ServiceLocater::_ss_instance = &_default_ss;
