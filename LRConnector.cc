// Copyright 2016 oneup

#include "LRConnector.hpp"

namespace gblr {

LRConnector::LRConnector()
	: m_(this),
	  environment_(nullptr),
	  video_refresh_(nullptr),
	  audio_sample_(nullptr), audio_sample_batch_(nullptr),
	  input_poll_(nullptr), input_state_(nullptr)
{}

unsigned LRConnector::ApiVersion() { return RETRO_API_VERSION; }

void LRConnector::Run() {
	input_poll_();

	m_.ResetFrame();

	while (!m_.FrameReady()) {
		m_.Tick();
	}

	video_refresh_(m_.GetFrame(), 160, 144, 160*4);
}

bool LRConnector::LoadGame(const struct retro_game_info *game) {
	return m_.LoadGame(game);
}

void LRConnector::UnloadGame() {
	m_.UnloadGame();
}

void LRConnector::GetSystemInfo(retro_system_info *info) {
	info->library_name = name_;
	info->library_version = version_;
	info->valid_extensions = extensions_;
	info->need_fullpath = false;
	info->block_extract = false;
}

void LRConnector::GetSystemAVInfo(retro_system_av_info *info) {
	info->geometry.base_width = width_;
	info->geometry.base_height = height_;
	info->geometry.max_width = width_;
	info->geometry.max_height = height_;
	info->geometry.aspect_ratio = 0.0;

	info->timing.fps = fps_;
	info->timing.sample_rate = sample_rate_;

	SetPixelFormat(RETRO_PIXEL_FORMAT_XRGB8888);
}

MemDescriptor LRConnector::GetSystemRAM() {
	return MemDescriptor{m_.wram.data(), m_.wram.size()};
}

MemDescriptor LRConnector::GetSaveRAM() {
	return MemDescriptor{nullptr, 0};
}

MemDescriptor LRConnector::GetRTC() {
	return MemDescriptor{nullptr, 0};
}

MemDescriptor LRConnector::GetVRAM() {
	return MemDescriptor{m_.lcd.vram.data(), m_.lcd.vram.size()};
}

MemDescriptor LRConnector::GetMemory(unsigned id) {
	switch (id) {
		case RETRO_MEMORY_SYSTEM_RAM:	return GetSystemRAM();
		case RETRO_MEMORY_SAVE_RAM:		return GetSaveRAM();
		case RETRO_MEMORY_RTC:			return GetRTC();
		case RETRO_MEMORY_VIDEO_RAM:	return GetVRAM();
		default:						return MemDescriptor();
	}
}

void* LRConnector::GetMemoryData(unsigned id) {
	return GetMemory(id).data;
}
size_t LRConnector::GetMemorySize(unsigned id) {
	return GetMemory(id).size;
}

bool LRConnector::SetPixelFormat(enum retro_pixel_format fmt) {
	return environment_(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt);
}

Button LRConnector::PollInput() {
	gblr::u8 btn = 0;
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN)) 		{ btn |= gblr::BTN_DOWN; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP)) 		{ btn |= gblr::BTN_UP; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT)) 		{ btn |= gblr::BTN_LEFT; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT)) 	{ btn |= gblr::BTN_RIGHT; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START)) 	{ btn |= gblr::BTN_START; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT)) 	{ btn |= gblr::BTN_SELECT; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)) 		{ btn |= gblr::BTN_B; }
	if (input_state_(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A)) 		{ btn |= gblr::BTN_A; }

	return gblr::Button(btn);
}

}	// namespace gblr
