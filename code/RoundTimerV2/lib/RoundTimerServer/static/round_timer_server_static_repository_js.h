#include <Arduino.h>

const char round_timer_server_static_repository_js[] PROGMEM = R"rawliteral(

function prepareFormData(input) {
    const form_data = new FormData()
    Object.keys(input).forEach((key) => {
        form_data.append(key, input[key])
    })
    return form_data
}


async function saveStaCredentialsRepository(input) {
    try {
        const result = await fetch('/api/sta-credentials',
            {
                body: prepareFormData(input),
                method: 'POST',
            }
        )
        return result.json()
    } catch (error) {
        console.log('saveStaCredentialsRepository - Error:', error)
        return {}
    }
}


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
        return {}
    }
}


async function setControlsRepository(input) {
    try {
        await fetch('/api/controls',
            {
                body: prepareFormData(input),
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('setControlsRepository - Error:', error)
    }
}


async function setLampColorRepository(input) {
    try {
        await fetch('/api/lamps',
            {
                body: prepareFormData(input),
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('setLampColorRepository - Error:', error)
    }
}


async function saveRoundTimerConfigurationRepository(input) {
    try {
        await fetch('/api/round-timer-configurations',
            {
                body: prepareFormData(input),
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('saveRoundTimerConfigurationRepository - Error:', error)
    }
}


async function saveSaveLampPresetRepository(input) {
    try {
        await fetch('/api/lamps-presets',
            {
                body: prepareFormData(input),
                method: 'POST',
            }
        )
    } catch (error) {
        console.log('saveSaveLampPresetRepository - Error:', error)
    }
}


async function deleteStaCredentialsFileRepository() {
    try {
        await fetch('/api/remove-sta-credentials-file',
            {
                method: 'DELETE',
            }
        )
    } catch (error) {
        console.log('deleteStaCredentialsFileRepository - Error:', error)
    }
}


async function deleteConfigurationsFileRepository() {
    try {
        await fetch('/api/remove-configurations-file',
            {
                method: 'DELETE',
            }
        )
    } catch (error) {
        console.log('deleteConfigurationsFileRepository - Error:', error)
    }
}


async function deleteLampsPresetsFileRepository() {
    try {
        await fetch('/api/remove-lamps-presets-file',
            {
                method: 'DELETE',
            }
        )
    } catch (error) {
        console.log('deleteLampsPresetsFileRepository - Error:', error)
    }
}
)rawliteral";

