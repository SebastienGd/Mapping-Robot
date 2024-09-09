// SpecificConfiguration contains an enum that shows all available
// prescalers (with the corresponding getPrescalerValue function). It also
// contains getWgmConfigurationA/B functions that gives the need bits for
// TCCRnA/B according to the specified waveform generation mode

#ifndef TIMER_SPECIFIC_CONFIGURATION_H
#define TIMER_SPECIFIC_CONFIGURATION_H
#include "TimerConfiguration.h"

template<TimerNumber timerNumber>
struct SpecificConfiguration {
    enum Prescaler {
    };

    static const uint8_t getPrescalerValue(const Prescaler& prescaler);
    static const uint8_t getWgmConfigurationA(const WaveformMode& mode);
    static const uint8_t getWgmConfigurationB(const WaveformMode& mode);
};

// TIMER_0 configuration (shares TIMER_1 Prescaler,
//                        shares TIMER_2 WGM configurations and interrupt mode)
template<>
struct SpecificConfiguration<TimerNumber::TIMER_0> {

    enum Prescaler {
        NO_CLK = 0,
        DIVISOR_1 = (1 << CS10),
        DIVISOR_8 = (1 << CS11),
        DIVISOR_64 = (1 << CS11) | (1 << CS10),
        DIVISOR_256 = (1 << CS12),
        DIVISOR_1024 = (1 << CS12) | (1 << CS10)
    };

    static const uint16_t getPrescalerValue(const Prescaler& prescaler) {
        static constexpr uint16_t PRESCALER_VALUES[] = {0, 1, 8, 64, 256, 1024};
        return PRESCALER_VALUES[prescaler];
    }

    static const uint8_t getWgmConfigurationA(const WaveformMode& mode) {
        static constexpr uint8_t WGM_CONFIGURATIONS_A[] = {0,
                                                           (1 << WGM01),
                                                           (1 << WGM00),
                                                           (1 << WGM01) |
                                                               (1 << WGM00),
                                                           (1 << WGM00)};
        return WGM_CONFIGURATIONS_A[mode];
    }

    static const uint8_t getWgmConfigurationB(const WaveformMode& mode) {
        static constexpr uint8_t WGM_CONFIGURATIONS_B[] = {
            0, 0, 0, 0, (1 << WGM02)};
        return WGM_CONFIGURATIONS_B[mode];
    }
};

// TIMER_1 configuration (shares TIMER_0 Prescaler)
template<>
struct SpecificConfiguration<TimerNumber::TIMER_1> {

    using Prescaler = SpecificConfiguration<TimerNumber::TIMER_0>::Prescaler;

    static const uint16_t getPrescalerValue(const Prescaler& prescaler) {
        return SpecificConfiguration<TimerNumber::TIMER_0>::getPrescalerValue(
            prescaler);
    }

    static const uint8_t getWgmConfigurationA(const WaveformMode& mode) {
        static constexpr uint8_t WGM_CONFIGURATIONS_A[] = {
            0, 0, (1 << WGM10), (1 << WGM10), (1 << WGM10) | (1 << WGM11)};
        return WGM_CONFIGURATIONS_A[mode];
    }

    static const uint8_t getWgmConfigurationB(const WaveformMode& mode) {
        static constexpr uint8_t WGM_CONFIGURATIONS_B[] = {
            0, (1 << WGM12), 0, (1 << WGM12), (1 << WGM13)};
        return WGM_CONFIGURATIONS_B[mode];
    }
};

// TIMER_2 configuration (shares TIMER_0 WGM configurations and interrupt mode)
template<>
struct SpecificConfiguration<TimerNumber::TIMER_2> {

    enum Prescaler {
        NO_CLK = 0,
        DIVISOR_1 = (1 << CS20),
        DIVISOR_8 = (1 << CS21),
        DIVISOR_32 = (1 << CS21) | (1 << CS20),
        DIVISOR_64 = (1 << CS22),
        DIVISOR_128 = (1 << CS22) | (1 << CS20),
        DIVISOR_256 = (1 << CS22) | (1 << CS21),
        DIVISOR_1024 = (1 << CS22) | (1 << CS21) | (1 << CS20),
    };

    static const uint16_t getPrescalerValue(const Prescaler& prescaler) {
        static constexpr uint16_t PRESCALER_VALUES[] = {
            0, 1, 8, 32, 64, 128, 256, 1024};
        return PRESCALER_VALUES[prescaler];
    }

    static const uint8_t getWgmConfigurationA(const WaveformMode& mode) {
        return SpecificConfiguration<
            TimerNumber::TIMER_0>::getWgmConfigurationA(mode);
    }

    static const uint8_t getWgmConfigurationB(const WaveformMode& mode) {
        return SpecificConfiguration<
            TimerNumber::TIMER_0>::getWgmConfigurationB(mode);
    }
};
#endif
