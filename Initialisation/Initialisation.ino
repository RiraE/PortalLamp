// базовый пример работы с лентой, основные возможности
// библиотека microLED версии 3.0+
// для более подробной информации читай документацию
// константы для удобства
#define STRIP_PIN 9    // пин ленты
#define NUMLEDS 60      // кол-во светодиодов
// ===== ЦВЕТОВАЯ ГЛУБИНА =====
// 1, 2, 3 (байт на цвет)
// на меньшем цветовом разрешении скетч будет занимать в разы меньше места,
// но уменьшится и количество оттенков и уровней яркости!
// дефайн делается ДО ПОДКЛЮЧЕНИЯ БИБЛИОТЕКИ
// без него будет 3 байта по умолчанию
#define COLOR_DEBTH 3
#include <microLED.h>   // подключаем библу
// ======= ИНИЦИАЛИЗАЦИЯ =======
// <колво-ледов, пин, клок пин, чип, порядок>
// microLED<NUMLEDS, DATA_PIN, CLOCK_PIN, LED_WS2818, ORDER_GRB> strip;
// CLOCK пин нужен только для SPI лент (например APA102)
// для обычных WS лент указываем MLED_NO_CLOCK
// по APA102 смотри отдельный гайд в примерах
// различные китайские подделки могут иметь совместимость
// с одним чипом, но другой порядок цветов!
// поддерживаемые чипы лент и их официальный порядок цветов:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2811, ORDER_GBR> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2813, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2815, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS6812, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
// microLED<NUMLEDS, MLED_NO_CLOCK, MLED_NO_CLOCK, LED_APA102_SPI, ORDER_BGR> strip;  // для аппаратного SPI
// ======= ПРЕРЫВАНИЯ =======
// для повышения надёжности передачи данных на ленту можно отключать прерывания.
// В библиотеке есть 4 режима:
// CLI_OFF - прерывания не отключаются (возможны сбои в работе ленты)
// CLI_LOW - прерывания отключаются на время передачи одного цвета
// CLI_AVER - прерывания отключаются на время передачи одного светодиода (3 цвета)
// CLI_HIGH - прерывания отключаются на время передачи даных на всю ленту
// По умолчанию отключение прерываний стоит на CLI_OFF (не отключаются)
// Параметр передаётся 5ым при инициализации:
// microLED<NUMLEDS, STRIP_PIN, LED_WS2818, ORDER_GRB, CLI_AVER> strip;
// ======= СПАСИТЕ МИЛЛИС =======
// При отключении прерываний в режиме среднего и высокого проритета (CLI_AVER и CLI_HIGH)
// неизбежно будут чуть отставать функции времени millis() и micros()
// В библиотеке встроено обслуживание функций времени, для активации передаём SAVE_MILLIS
// 6-ым аргументом при инициализации:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER, SAVE_MILLIS> strip;
// это НЕЗНАЧИТЕЛЬНО замедлит вывод на ленту, но позволит миллису считать без отставания!
// инициализирую ленту (выше был гайд!)
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

uint8_t first_diode[4];

