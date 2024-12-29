/*****************************************************
 *                    MOCK SERVER                    *
 *****************************************************/

const SERVER_LAG_LONG = 1000;
const SERVER_LAG_SHORT = 500;

const repository_business_state = {
    device_mode: 1,
    ap_ssid: "RoundTimerAccessPoint",
    sta_ssid: "LiveboxLA",
    sta_password: "",
    sta_ip: "192.168.1.25",
    sta_is_connected: true,
    sta_is_configured: false,
    round_timer_step: 0,
    round_timer_mode: 1,
    round_timer_round_color: "#00FF00",
    round_timer_rest_color: "#FF0000",
    round_timer_prerest_color: "#FF4500",
    round_timer_round_long_duration: 18,
    round_timer_round_short_duration: 12,
    round_timer_rest_long_duration: 6,
    round_timer_rest_short_duration: 3,
    round_timer_prerest_duration: 3,
    round_timer_state_is_running: false,
    round_timer_state_is_round_long_duration: false,
    round_timer_state_is_rest_long_duration: false,
    lamp_0_color: '',
    lamp_1_color: '',
    lamp_2_color: '',
}

async function wait(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function getBusinessStateRepository() {
    console.log('getBusinessStateRepository')
    await wait(SERVER_LAG_SHORT);
    return repository_business_state
}


async function setControlsRepository(data) {
    console.log('setControls', data)
    await wait(SERVER_LAG_SHORT);
    Object.keys(data).forEach((key) => {
        repository_business_state[key] = data[key]
    })
    const params = {}
    return {
        status: 'ok',
    }
}


async function setLampColorRepository(data) {
    console.log('setLampColor', data)
    await wait(SERVER_LAG_SHORT);
    Object.keys(data).forEach((key) => {
        repository_business_state[key] = data[key]
    })
    const params = {}
    return {
        status: 'ok',
    }
}
