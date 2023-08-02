#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

const int SAMPLE_RATE = 44100; // Sample rate (samples per second)
const int AMPLITUDE = 28000;   // Amplitude of the sine wave

void audioCallback(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;

    // Convert the stream pointer to a Uint16 pointer
    Uint16* audioBuffer = reinterpret_cast<Uint16*>(stream);
    const int samples = len / sizeof(Uint16);

    for (int i = 0; i < samples; ++i) {
        // Generate a simple sine wave
        double sample = AMPLITUDE * std::sin(2.0 * M_PI * phase);
        audioBuffer[i] = static_cast<Uint16>(sample) + 32768; // Convert to 16-bit audio format
        phase += 440.0 / SAMPLE_RATE; // 440 Hz frequency (A4 note) as an example, change as desired
    }
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_AudioSpec spec;
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_S16SYS; // 16-bit signed audio format
    spec.channels = 1;          // Mono
    spec.samples = 4096;        // Buffer size (in samples)
    spec.callback = audioCallback;

    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        std::cerr << "SDL_OpenAudio Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_PauseAudio(0); // Start playing audio

    // Wait for a few seconds
    SDL_Delay(5000);

    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
