#include <Arduino.h>

const char round_timer_server_static_index_js[] PROGMEM = R"rawliteral(

/**
 * Generic methods
 */
function $(selector, element = document) {
    return element.querySelector(selector)
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


let business_state = {
    ap_ssid: '',
    sta_ssid: 'Livebox-data',
    sta_password: '',
    sta_ip: '192.168.1.4-data',
    sta_is_connected: false,
    sta_is_configured: false,
    firmware_version: '2.0.0-data',

    lamp_1_color: '#ff0000',
    lamp_2_color: '#00ff00',
    lamp_3_color: '',
}

/**
 * INIT
 */
document.addEventListener('DOMContentLoaded', async () => {
    const anchor = window.location.hash.substring(1) 
    if (anchor == '') {
        anchorLink('main-menu')
    } else {
        rmCls($(`#page-${anchor}`), 'hidden')
    }
    window.addEventListener("hashchange", (event) => {
        const oldHash = new URL(event.oldURL).hash.substring(1)
        const newHash = new URL(event.newURL).hash.substring(1)
        if (oldHash) {
            addCls($(`#page-${oldHash}`), 'hidden')
        }
        rmCls($(`#page-${newHash}`), 'hidden')
    })
    updateRender();
    initWifiCredentialsBlock();
})


function updateRender() {
    // configuration
    const _el_configuraion_info = $('.block-configuraion-info')
    $('.value_sta_ssid', _el_configuraion_info).textContent = business_state.sta_ssid
    $('.value_sta_ip', _el_configuraion_info).textContent = business_state.sta_ip
    $('.value_firmware_version', _el_configuraion_info).textContent = business_state.firmware_version

    const _el_round_timer_lamp_preview = $('.block-round-timer-lamp-preview')

    if (business_state.lamp_1_color === '') {
        $('.lamp-1', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-1', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_1_color
    }
    if (business_state.lamp_2_color === '') {
        $('.lamp-2', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-2', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_2_color
    }
    if (business_state.lamp_3_color === '') {
        $('.lamp-3', _el_round_timer_lamp_preview).style.backgroundColor = '#dce1e2'
    } else {
        $('.lamp-3', _el_round_timer_lamp_preview).style.backgroundColor = business_state.lamp_3_color
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
)rawliteral";

