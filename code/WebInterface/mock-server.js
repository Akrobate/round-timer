/*****************************************************
 *                    MOCK SERVER                    *
 *****************************************************/

const SERVER_LAG_LONG = 1000;
const SERVER_LAG_SHORT = 500;

async function wait(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function getBusinessState() {
    console.log('getBusinessState')
    await wait(SERVER_LAG_SHORT);
    return {
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
        lamp_0_color: "#010000",
        lamp_1_color: "#000022",
        lamp_2_color: "#003300"
    }
}


async function setControls(data) {
    console.log('setControls', data)
    const params = {}
    await wait(SERVER_LAG_SHORT);
    return {
        status: 'ok',
    }
}
