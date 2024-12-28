#include <Arduino.h>

const char round_timer_server_static_repository_js[] PROGMEM = R"rawliteral(

/**
 * test method
 * @returns {Promise<Array>}
 */
async function getBusinessState() {
    try {
        const result = await fetch('/api/business-state',
            {
                method: 'GET',
            }
        )
        return result.json()
    } catch (error) {
        console.log('serverGet - Error:', error)
        return []
    }
}
)rawliteral";

