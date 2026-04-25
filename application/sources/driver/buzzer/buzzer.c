#include "io_cfg.h"
#include <buzzer.h>
#include "tim.h"

volatile       uint32_t          _beep_duration;
volatile       bool              _tones_playing;
volatile const Tone_TypeDef     *_tones;

GPIO_InitTypeDef GPIO_InitStructure;
extern TIM_HandleTypeDef htim3;

void buzzer_irq( void ) {
	if (__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_UPDATE)
		&& __HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE))
	{
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);

		_beep_duration--;
		if (_beep_duration == 0) {
			if (_tones_playing) {
				// Currently playing tones, take next tone
				_tones++;
				if (_tones->frequency == 0 && _tones->duration == 0) {
					// Last tone in sequence
					BUZZER_Disable();
					_tones_playing = false;
					_tones = NULL;
				} else {
					if (_tones->frequency == 0) {
						// Silence period
						__HAL_TIM_SET_AUTORELOAD(&htim3, (SystemCoreClock / (100 * htim3.Init.Prescaler) - 1));
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
						_beep_duration = _tones->duration + 1;
					} else {
						// Play next tone in sequence
						BUZZER_Enable(_tones->frequency,_tones->duration);
					}
				}
			} else {
				BUZZER_Disable();
			}
		}
	}
}

// Initialize buzzer output
void BUZZER_Init(void) {
	MX_TIM3_Init();

	// /* BUZZER TIM enable counter */
	HAL_TIM_Base_Start_IT(&htim3);

	// /* BUZZER disable */
	gpio_init_pin(BUZZER_IO_PORT, BUZZER_IO_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

// Turn on buzzer with specified frequency
// input:
//   freq - PWM frequency for buzzer (Hz)
//   duration - duration of buzzer work (tens ms: 1 -> 10ms sound duration)
void BUZZER_Enable(uint16_t freq, uint32_t duration) {
	if (freq < 100 || freq > 8000 || duration == 0) {
		BUZZER_Disable();
	} else {
		_beep_duration = (freq / 100) * duration + 1;

		// // Configure buzzer pin
		HAL_TIM_MspPostInit(&htim3);

		// // Configure and enable PWM timer
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_TIM_SET_AUTORELOAD(&htim3, SystemCoreClock / (freq * htim3.Init.Prescaler) - 1);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, __HAL_TIM_GetAutoreload(&htim3) >> 1); // 50% duty cycle
		HAL_TIM_Base_Start_IT(&htim3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	}
}

// Turn off buzzer
void BUZZER_Disable(void) {
	HAL_TIM_Base_Stop_IT(&htim3);
	__HAL_RCC_TIM3_CLK_DISABLE();
	// // Configure buzzer pin as analog input without pullup to conserve power
	gpio_init_pin(BUZZER_IO_PORT, BUZZER_IO_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

// Start playing tones sequence
// input:
//   tones - pointer to tones array
void BUZZER_PlayTones(const Tone_TypeDef * tones) {
	_tones = tones;
	_tones_playing = true;
	BUZZER_Enable(_tones->frequency,_tones->duration);
}
