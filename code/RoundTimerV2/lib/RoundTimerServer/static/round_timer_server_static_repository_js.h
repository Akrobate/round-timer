#include <Arduino.h>

const char round_timer_server_static_repository_js[] PROGMEM = R"rawliteral(

/**
 * test method
 * @returns {Promise<Array>}
 */
async function getBusinessStateRepository() {
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


async function setControlsRepository(input) {
    try {
        const form_data = new FormData()
        Object.keys(input).forEach((key) => {
            form_data.append(key, input[key])
        })
        await fetch('/api/controls',
            {
                body: form_data,
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('setControlsRepository - Error:', error)
    }
}


async function setLampColorRepository(input) {
    try {
        const form_data = new FormData()
        Object.keys(input).forEach((key) => {
            form_data.append(key, input[key])
        })
        await fetch('/api/lamps',
            {
                body: form_data,
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('setLampColorRepository - Error:', error)
    }
}
)rawliteral";

