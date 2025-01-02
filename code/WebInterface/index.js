
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
        btn.textContent = 'Chargement...'
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

    sta_credentials_file_exists: false,
    configurations_file_exists: false,
    lamps_presets_file_exists: false,

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

    lamp_preset_list: [],
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

    // saved files
    updateBlockSavedFiles()
}


function updateBlockSavedFiles() {
    const _el_block_saved_files = $('.block-saved-files')
    updateSavedFileLine(business_state.sta_credentials_file_exists, 'list-item-sta-credentials', _el_block_saved_files)
    updateSavedFileLine(business_state.configurations_file_exists, 'list-item-configurations', _el_block_saved_files)
    updateSavedFileLine(business_state.lamps_presets_file_exists, 'list-item-lamps-presets', _el_block_saved_files)

    if (
        !business_state.sta_credentials_file_exists
        && !business_state.configurations_file_exists
        && !business_state.lamps_presets_file_exists
    ) {
        rmCls($('h4', _el_block_saved_files), 'hidden')
        addCls($('ul', _el_block_saved_files), 'hidden')
    } else {
        addCls($('h4', _el_block_saved_files), 'hidden')
        rmCls($('ul', _el_block_saved_files), 'hidden')
    }
}



// Saved files block file
function updateSavedFileLine(is_visible, li_class, parent_element) {
    const _el = $(`.${li_class}`, parent_element)
    if (is_visible) {
        addCls(_el, 'list-item')
        rmCls(_el, 'hidden')
    } else {
        rmCls(_el, 'list-item')
        addCls(_el, 'hidden')
    }
}

async function deleteStaCredentialsFile(btn) {
    buttonSetLoadingState(btn, true)
    await deleteStaCredentialsFileRepository()
    business_state = await getBusinessStateRepository()
    updateBlockSavedFiles()
    buttonSetLoadingState(btn, false)
}

async function deleteConfigurationsFile(btn) {
    buttonSetLoadingState(btn, true)
    await deleteConfigurationsFileRepository()
    business_state = await getBusinessStateRepository()
    updateBlockSavedFiles()
    buttonSetLoadingState(btn, false)

}

async function deleteLampsPresetsFile(btn) {
    buttonSetLoadingState(btn, true)
    await deleteLampsPresetsFileRepository()
    business_state = await getBusinessStateRepository()
    updateBlockSavedFiles()
    buttonSetLoadingState(btn, false)
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

function saveWifiCredentials(btn) {
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

    buttonSetLoadingState(btn, true)
    console.log('Saving wifi credentials...')
    console.log('SSID:', name)
    console.log('Password', password)
    buttonSetLoadingState(btn, false)
}

// Controls
async function setControls(data) {
    await setControlsRepository(data)
    business_state = await getBusinessStateRepository()
    updateRender()
}


// Lamps

let selected_preset_index = null

async function pageLampMounted() {
    console.log("pageLampMounted in method")
    business_state = await getBusinessStateRepository()
    updateLampPresets()
    updatePresetSelection()
}


function updateLampPresets() {
    const preset_list = business_state.lamp_preset_list

    const _el = $('.block-lamp-presets')
    const _list_el = $('.color-presets', _el)
    _list_el.innerHTML = ''
    const template_html = $('#template-color-preset').innerHTML
    
    preset_list.forEach((data, index) => {
        let html = template_html
        Object.keys(data).forEach((key) => {
            html = html.replaceAll(`{{ color_${key} }}`, data[key]);
        })
        html = html.replaceAll('{{ index }}', index);
        const _new_el = document.createElement("div")
        _new_el.innerHTML = html
        $('.color_0', _new_el).style.backgroundColor = data[0]
        $('.color_1', _new_el).style.backgroundColor = data[1]
        $('.color_2', _new_el).style.backgroundColor = data[2]
        _list_el.appendChild(_new_el.firstElementChild)
    })

}

function setLampInputColors(color_0, color_1, color_2) {
    const _el = $('.block-lamp-controls')
    $('input[name=lamp_0_color]', _el).value = color_0
    $('input[name=lamp_1_color]', _el).value = color_1
    $('input[name=lamp_2_color]', _el).value = color_2
}

function getLampInputColors() {
    const _el = $('.block-lamp-controls')
    return {
        lamp_0_color: $('input[name=lamp_0_color]', _el).value,
        lamp_1_color: $('input[name=lamp_1_color]', _el).value,
        lamp_2_color: $('input[name=lamp_2_color]', _el).value,
    }
}

function displayPresetColors(color_0, color_1, color_2, preset_index) {
    if (selected_preset_index === Number(preset_index)) {
        setLampInputColors('#000000', '#000000', '#000000')
        selected_preset_index = null
    } else {
        setLampInputColors(color_0, color_1, color_2)
        selected_preset_index = Number(preset_index)
    }
    updatePresetSelection()
    updateLampsColors()
}

function updatePresetSelection() {

    const _el_control = $('.block-lamp-controls')
    if (selected_preset_index !== null) {
        rmCls($('.save-preset-button', _el_control), 'hidden')
    } else {
        addCls($('.save-preset-button', _el_control), 'hidden')
    }

    const selected_class = 'preset-selected'
    const _el = $('.block-lamp-presets')
    $all('.preset-icon', _el).forEach((el) => {
        rmCls(el, selected_class)
    });
    if (selected_preset_index !== null) {
        console.log(`.lamp-preset-index-${selected_preset_index}`)
        addCls($(`.lamp-preset-index-${selected_preset_index}`, _el), selected_class)
    }
}

async function saveCurrentPreset(btn) {
    buttonSetLoadingState(btn, true)
    await saveSaveLampPresetRepository({
        index: selected_preset_index,
        ...getLampInputColors(),
    })
    business_state = await getBusinessStateRepository()
    updateLampPresets()
    updatePresetSelection()
    buttonSetLoadingState(btn, false)
}

async function updateLampsColors() {
    await setLampColor(getLampInputColors())
}

async function setLampColor(data) {
    setLampInputColors(data.lamp_0_color, data.lamp_1_color, data.lamp_2_color)
    await setLampColorRepository(data)
}


// RoundTimer Configuration
async function pageRoundTimerConfigurationsMounted() {
    business_state = await getBusinessStateRepository()
    const _el = $('#page-round-timer-configurations')

    $all('input[name=round_timer_mute]', _el).forEach((radio) => {
        if (business_state.round_timer_mute) {
            radio.checked = true;
        } else {
            radio.checked = false;
        }
    });

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


async function setRoundTimerConfiguration(btn) {
    buttonSetLoadingState(btn, true)
    const _el = $('#page-round-timer-configurations')
    const data = {

        round_timer_mute: $('input[name=round_timer_mute]:checked', _el) ? true : false,

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
    buttonSetLoadingState(btn, false)
}

