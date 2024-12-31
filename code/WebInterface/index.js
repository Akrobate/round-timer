
/**
 * Generic methods
 */
function $(selector, element = document) {
    return element.querySelector(selector)
}

function $all(selector, element = document) {
    return element.querySelectorAll(selector)
}

function buttonSetLoadingState(btn, state) {
    btn.disabled = state
    if (state) {
        btn.dataset.originalText = btn.textContent
        btn.textContent = 'Loading...'
    } else {
        btn.textContent = btn.dataset.originalText
    }
}

const addCls = (_el, _cls) => _el.classList.add(_cls)
const rmCls = (_el, _cls) => _el.classList.remove(_cls)

function isValidUrl(string) {
    try {
      new URL(string)
      return true
    } catch (_) {
      return false
    }
}

function anchorLink(anchor) {
    window.location.hash = anchor
}

function formatTime(date_time_string) {
    const date = new Date(date_time_string)
    const hours = date.getHours().toString().padStart(2, '0')
    const minutes = date.getMinutes().toString().padStart(2, '0')
    return `${hours}:${minutes}`;
}


/**
 * business_state
 */

let business_state = {
    ap_ssid: '',
    sta_ssid: 'Livebox-data',
    sta_password: '',
    sta_ip: '192.168.1.4-data',
    sta_is_connected: false,
    sta_is_configured: false,
    firmware_version: '2.0.0-data',

    round_timer_mute: false,

    // ROUND_TIMER_SEQUENTIAL_MODE = 1
    // ROUND_TIMER_ALL_MODE = 2
    round_timer_mode: 1, 

    // ASC 0, DESC 1
    round_timer_sequential_mode_order: 0,

    round_timer_round_color: '#00FF00',
    round_timer_rest_color: '#FF0000',
    round_timer_prerest_color: '#FF4500',

    round_timer_round_long_duration: 0,
    round_timer_round_short_duration: 0,
    round_timer_rest_long_duration: 0,
    round_timer_rest_short_duration: 0,
    round_timer_prerest_duration: 0,
    round_timer_prestart_duration: 0,

    round_timer_state_is_running: false,
    round_timer_state_is_round_long_duration: false,
    round_timer_state_is_rest_long_duration: false,

    lamp_0_color: '',
    lamp_1_color: '',
    lamp_2_color: '',
}


let business_state_interval_handler = null

/**
 * INIT
 */
document.addEventListener('DOMContentLoaded', async () => {
    const anchor = window.location.hash.substring(1) 
    if (anchor == '') {
        anchorLink('main-menu')
    } else {
        rmCls($(`#page-${anchor}`), 'hidden')
        const init_function = snakeToCamel(`page-${anchor}-mounted`)
        if (typeof window[init_function] === 'function') {
            console.log('Init function:', init_function)
            window[init_function]();
        } else {
            console.log('-----Init function:', init_function)
        }
    }
    window.addEventListener("hashchange", (event) => {
        const oldHash = new URL(event.oldURL).hash.substring(1)
        const newHash = new URL(event.newURL).hash.substring(1)
        if (oldHash) {
            addCls($(`#page-${oldHash}`), 'hidden')
            const unmounted_function = snakeToCamel(`page-${oldHash}-unmounted`)
            if (typeof window[unmounted_function] === 'function') {
                console.log('unmounted_function:', unmounted_function)
                window[unmounted_function]();
            } else {
                console.log('unmounted_function:', unmounted_function)
            }
        }
        rmCls($(`#page-${newHash}`), 'hidden')

        const init_function = snakeToCamel(`page-${newHash}-mounted`)
        if (typeof window[init_function] === 'function') {
            console.log('init_function:', init_function)
            window[init_function]();
        } else {
            console.log('init_function:', init_function)
        }
    })
    business_state = await getBusinessStateRepository()
    updateRender();
    initWifiCredentialsBlock();

    // init update business state timer
    business_state_interval_handler = setInterval(async () => {
        business_state = await getBusinessStateRepository()
        updateRender()
    }, 1000)
})


function snakeToCamel(snake_string) {
    return snake_string
        .split('-')
        .map((word, index) =>
            index === 0 ? word : word.charAt(0).toUpperCase() + word.slice(1)
        )
        .join('')
}


function updateRender() {
    // configuration
    const _el_configuraion_info = $('.block-configuraion-info')
    $('.value_sta_ssid', _el_configuraion_info).textContent = business_state.sta_ssid
    $('.value_sta_ip', _el_configuraion_info).textContent = business_state.sta_ip
    $('.value_firmware_version', _el_configuraion_info).textContent = business_state.firmware_version

    // round timer lamps
    const _el_round_timer_lamp_preview = $('.block-round-timer-lamp-preview')
    if (['', '#000000'].includes(business_state.lamp_0_color)) {
        $('.lamp-0', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-0', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_0_color
    }
    if (['', '#000000'].includes(business_state.lamp_1_color)) {
        $('.lamp-1', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-1', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_1_color
    }
    if (['', '#000000'].includes(business_state.lamp_2_color)) {
        $('.lamp-2', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-2', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_2_color
    }

    // round timer controls
    const _el_round_timer_controls = $('.block-round-timer-controls')
    updateToggleButtonsControls(business_state.round_timer_state_is_running, 'round_timer_state_is_running', _el_round_timer_controls)
    updateToggleButtonsControls(business_state.round_timer_state_is_round_long_duration, 'round_timer_state_is_round_long_duration', _el_round_timer_controls)
    updateToggleButtonsControls(business_state.round_timer_state_is_rest_long_duration, 'round_timer_state_is_rest_long_duration', _el_round_timer_controls)
}

// Toggle button controls update
function updateToggleButtonsControls(value, class_prefix, parent_element) {
    const _el_true = $(`.${class_prefix}_true`, parent_element)
    const _el_false = $(`.${class_prefix}_false`, parent_element)
    if (value) {
        addCls(_el_true, 'primary')
        rmCls(_el_true, 'disabled')
        addCls(_el_false, 'disabled')
        rmCls(_el_false, 'primary')
    } else {
        addCls(_el_true, 'disabled')
        rmCls(_el_true, 'primary')
        addCls(_el_false, 'primary')
        rmCls(_el_false, 'disabled')
    }
}


// ****** Block: Wifi Credentials ******

function initWifiCredentialsBlock() {
    const _el_bwc = $('.bloc-wifi-credentials')
    if (business_state.sta_ssid) {
        $('.input-wifi-ssid', _el_bwc).value = business_state.sta_ssid
    }
}

function saveWifiCredentials() {
    const _el = $('.bloc-wifi-credentials')
    const _name_input = $('.input-wifi-ssid', _el)
    const _password_input = $('.input-wifi-password', _el)
    const name = _name_input.value
    const password = _password_input.value

    if (name.length == 0) {
        addCls(_name_input, 'error')
        return
    }
    
    if (password.length == 0) {
        addCls(_password_input, 'error')
        return
    }
    
    rmCls(_name_input, 'error')
    rmCls(_password_input, 'error')

    console.log('Saving wifi credentials...')
    console.log('SSID:', name)
    console.log('Password', password)
}

// Controls
async function setControls(data) {
    await setControlsRepository(data)
    business_state = await getBusinessStateRepository()
    updateRender()
}


// Lamps
async function setLampColor(data) {
    await setLampColorRepository(data)
}

async function updateLampsColors() {
    const _el = $('.block-lamp-controls')
    const lamp_0_color = $('input[name=lamp_0_color]', _el).value
    const lamp_1_color = $('input[name=lamp_1_color]', _el).value
    const lamp_2_color = $('input[name=lamp_2_color]', _el).value

    const data = {
        lamp_0_color,
        lamp_1_color,
        lamp_2_color,
    }
    await setLampColor(data)
}

async function pageRoundTimerConfigurationsMounted() {
    business_state = await getBusinessStateRepository()
    const _el = $('#page-round-timer-configurations')

    $all('input[name=round_timer_mode]', _el).forEach((radio) => {
        if (radio.value == business_state.round_timer_mode) {
            radio.checked = true;
        }
    });

    $all('input[name=round_timer_sequential_mode_order]', _el).forEach((radio) => {
        if (radio.value == business_state.round_timer_sequential_mode_order) {
            radio.checked = true;
        }
    });

    $('input[name=round_timer_round_color]', _el).value = business_state.round_timer_round_color
    $('input[name=round_timer_rest_color]', _el).value = business_state.round_timer_rest_color
    $('input[name=round_timer_prerest_color]', _el).value = business_state.round_timer_prerest_color

    $('input[name=round_timer_round_long_duration]', _el).value = business_state.round_timer_round_long_duration
    $('input[name=round_timer_round_short_duration]', _el).value = business_state.round_timer_round_short_duration
    $('input[name=round_timer_rest_long_duration]', _el).value = business_state.round_timer_rest_long_duration
    $('input[name=round_timer_rest_short_duration]', _el).value = business_state.round_timer_rest_short_duration
    $('input[name=round_timer_prerest_duration]', _el).value = business_state.round_timer_prerest_duration
    $('input[name=round_timer_prestart_duration]', _el).value = business_state.round_timer_prestart_duration
}


// RoundTimer Configuration
async function setRoundTimerConfiguration() {
    const _el = $('#page-round-timer-configurations')
    const data = {

        round_timer_mode: $('input[name=round_timer_mode]:checked', _el)?.value,
        round_timer_sequential_mode_order: $('input[name=round_timer_sequential_mode_order]:checked', _el)?.value,

        round_timer_round_color: $('input[name=round_timer_round_color]', _el).value,
        round_timer_rest_color: $('input[name=round_timer_rest_color]', _el).value,
        round_timer_prerest_color: $('input[name=round_timer_prerest_color]', _el).value,

        round_timer_round_long_duration: $('input[name=round_timer_round_long_duration]', _el).value,
        round_timer_round_short_duration: $('input[name=round_timer_round_short_duration]', _el).value,
        round_timer_rest_long_duration: $('input[name=round_timer_rest_long_duration]', _el).value,
        round_timer_rest_short_duration: $('input[name=round_timer_rest_short_duration]', _el).value,
        round_timer_prerest_duration: $('input[name=round_timer_prerest_duration]', _el).value,
        round_timer_prestart_duration: $('input[name=round_timer_prestart_duration]', _el).value,
    }
    await saveRoundTimerConfigurationRepository(data)
    console.log('Setting round timer configuration...')
    console.log(data)

}

