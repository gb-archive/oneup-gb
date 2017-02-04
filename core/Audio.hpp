#pragma once

// Copyright 2016 oneup

#include <array>

#include "Base.hpp"
#include "Serializer.hpp"

namespace gb1 {

class Channel1;
class Channel2;
class Channel3;
class Channel4;
class Audio;

static inline Serializer& operator<<(Serializer &s, const Channel1 &ch);
static inline Deserializer& operator>>(Deserializer &d, Channel1 &ch);

static inline Serializer& operator<<(Serializer &s, const Channel2 &ch);
static inline Deserializer& operator>>(Deserializer &d, Channel2 &ch);

static inline Serializer& operator<<(Serializer &s, const Channel3 &ch);
static inline Deserializer& operator>>(Deserializer &d, Channel3 &ch);

static inline Serializer& operator<<(Serializer &s, const Channel4 &ch);
static inline Deserializer& operator>>(Deserializer &d, Channel4 &ch);

static inline Serializer& operator<<(Serializer &s, const Audio &audio);
static inline Deserializer& operator>>(Deserializer &d, Audio &audio);

struct Machine;

class Channel1 {
    friend struct Machine;

    Audio &audio;
    friend class Audio;

    u8 r0_, r1_, r2_, r3_, r4_;
	u8 sweep_div_;
	u8 vol_, vol_div_;
    unsigned ctr_, step_;

    u8 vout_;

    static constexpr const u8 version_ = 0x00;
    static constexpr const u64 code_ = eight_cc(version_, 'c','h','a','n','1');
    friend Serializer& operator<<(Serializer &s, const Channel1 &ch);
    friend Deserializer& operator>>(Deserializer &d, Channel1 &ch);

    void TickSweep();
    void TickVolume();
    void TickLength();
    void TickOutput();
public:
    Channel1(Audio &audio);
    Channel1(const Channel1&) = delete;
    Channel1(Channel1&&) = delete;
    Channel1& operator=(const Channel1&) = delete;
    Channel1& operator=(Channel1&&) = delete;

    void Write(unsigned n, u8 val, bool force);
};

static inline Serializer& operator<<(Serializer &s, const Channel1 &ch) {
    s.Start(Channel1::code_);

    return s << ch.r0_ << ch.r1_ << ch.r2_ << ch.r3_ << ch.r4_
             << ch.sweep_div_
             << ch.vol_ << ch.vol_div_
             << ch.ctr_ << ch.step_
             << ch.vout_;
}

static inline Deserializer& operator>>(Deserializer &d, Channel1 &ch) {
    d.Start(Channel1::code_);

    return d >> ch.r0_ >> ch.r1_ >> ch.r2_ >> ch.r3_ >> ch.r4_
             >> ch.sweep_div_
             >> ch.vol_ >> ch.vol_div_
             >> ch.ctr_ >> ch.step_
             >> ch.vout_;
}

class Channel2 {
    friend struct Machine;

    Audio &audio;
    friend class Audio;

    u8 r0_, r1_, r2_, r3_, r4_;
	u8 vol_, vol_div_;
    unsigned ctr_, step_;

	u8 vout_;

    static constexpr const u8 version_ = 0x00;
    static constexpr const u64 code_ = eight_cc(version_, 'c','h','a','n','2');
    friend Serializer& operator<<(Serializer &s, const Channel2 &ch);
    friend Deserializer& operator>>(Deserializer &d, Channel2 &ch);

    void TickVolume();
    void TickLength();
    void TickOutput();
public:
    Channel2(Audio &audio);
    Channel2(const Channel2&) = delete;
    Channel2(Channel2&&) = delete;
    Channel2& operator=(const Channel2&) = delete;
    Channel2& operator=(Channel2&&) = delete;

    void Write(unsigned n, u8 val, bool force);
};

static inline Serializer& operator<<(Serializer &s, const Channel2 &ch) {
    s.Start(Channel2::code_);

    return s << ch.r0_ << ch.r1_ << ch.r2_ << ch.r3_ << ch.r4_
             << ch.vol_ << ch.vol_div_
             << ch.ctr_ << ch.step_
             << ch.vout_;
}

static inline Deserializer& operator>>(Deserializer &d, Channel2 &ch) {
    d.Start(Channel2::code_);

    return d >> ch.r0_ >> ch.r1_ >> ch.r2_ >> ch.r3_ >> ch.r4_
             >> ch.vol_ >> ch.vol_div_
             >> ch.ctr_ >> ch.step_
             >> ch.vout_;
}

class Channel3 {
	friend struct Machine;

	Audio &audio;
	friend class Audio;

	u8 r0_, r1_, r2_, r3_, r4_;
	unsigned ctr_, ndx_;

	u8 vout_;

	std::array<u8, 16> wave_;

	static constexpr const u8 version_ = 0x00;
	static constexpr const u64 code_ = eight_cc(version_, 'c', 'h', 'a', 'n', '3');
	friend Serializer& operator<<(Serializer &s, const Channel3 &ch);
	friend Deserializer& operator>>(Deserializer &d, Channel3 &ch);

	void TickLength();
	void TickOutput();
public:
	Channel3(Audio &audio);
	Channel3(const Channel3&) = delete;
	Channel3(Channel3&&) = delete;
	Channel3& operator=(const Channel3&) = delete;
	Channel3& operator=(Channel3&&) = delete;

	void Write(unsigned n, u8 val, bool force);
	void WriteWave(unsigned n, u8 val);
};

static inline Serializer& operator<<(Serializer &s, const Channel3 &ch) {
    s.Start(Channel3::code_);

    return s << ch.r0_ << ch.r1_ << ch.r2_ << ch.r3_ << ch.r4_
             << ch.ctr_ << ch.ndx_
             << ch.vout_
             << ch.wave_;
}

static inline Deserializer& operator>>(Deserializer &d, Channel3 &ch) {
    d.Start(Channel3::code_);

    return d >> ch.r0_ >> ch.r1_ >> ch.r2_ >> ch.r3_ >> ch.r4_
             >> ch.ctr_ >> ch.ndx_
             >> ch.vout_
             >> ch.wave_;
}

class Channel4 {
	friend struct Machine;

	Audio &audio;
	friend class Audio;

	u8 r0_, r1_, r2_, r3_, r4_;
	u8 vol_, vol_div_;
	u16 lsfr_;
	u32 lsfr_div_;

	u8 vout_;

	static constexpr const u8 version_ = 0x00;
	static constexpr const u64 code_ = eight_cc(version_, 'c', 'h', 'a', 'n', '4');
	friend Serializer& operator<<(Serializer &s, const Channel4 &ch);
	friend Deserializer& operator >> (Deserializer &d, Channel4 &ch);

	void TickVolume();
	void TickLength();
	void TickOutput();
public:
	Channel4(Audio &audio);
	Channel4(const Channel4&) = delete;
	Channel4(Channel4&&) = delete;
	Channel4& operator=(const Channel4&) = delete;
	Channel4& operator=(Channel4&&) = delete;

	void Write(unsigned n, u8 val, bool force);
};

static inline Serializer& operator<<(Serializer &s, const Channel4 &ch) {
    s.Start(Channel4::code_);

    return s << ch.r0_ << ch.r1_ << ch.r2_ << ch.r3_ << ch.r4_
             << ch.vol_ << ch.vol_div_
             << ch.lsfr_ << ch.lsfr_div_
             << ch.vout_;
}

static inline Deserializer& operator>>(Deserializer &d, Channel4 &ch) {
    d.Start(Channel4::code_);

    return d >> ch.r0_ >> ch.r1_ >> ch.r2_ >> ch.r3_ >> ch.r4_
             >> ch.vol_ >> ch.vol_div_
             >> ch.lsfr_ >> ch.lsfr_div_
             >> ch.vout_;
}

class Audio {
    Machine *m_;
    friend struct Machine;

    Channel1 ch1_;
    friend class Channel1;

    Channel2 ch2_;
    friend class Channel2;

	Channel3 ch3_;
	friend class Channel3;

	Channel4 ch4_;
	friend class Channel4;

    u8 nr50_, nr51_, nr52_;
    unsigned sample_div_, timer_div_, seq_step_;

    static constexpr const u8 version_ = 0x00;
    static constexpr const u64 code_ = eight_cc(version_, 'a','u','d','i','o');
    friend Serializer& operator<<(Serializer &s, const Audio &audio);
    friend Deserializer& operator>>(Deserializer &d, Audio &audio);

    void TickLength();
    void TickSweep();
    void TickVolume();
	void TickOutput();

    void GenerateSample();
public:
    Audio(Machine *m);
    Audio(const Audio&) = delete;
    Audio(Audio&&) = delete;
    Audio& operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) = delete;

    bool Tick();
    void Write(u16 addr, u8 val, bool force);
};

static inline Serializer& operator<<(Serializer &s, const Audio &audio) {
    s.Start(Audio::code_);

    return s << audio.ch1_
             << audio.nr50_ << audio.nr51_ << audio.nr52_
             << audio.timer_div_ << audio.seq_step_;
}

static inline Deserializer& operator>>(Deserializer &d, Audio &audio) {
    d.Start(Audio::code_);

    return d >> audio.ch1_
             >> audio.nr50_ >> audio.nr51_ >> audio.nr52_
             >> audio.timer_div_ >> audio.seq_step_;
}

}   // namespace gb1