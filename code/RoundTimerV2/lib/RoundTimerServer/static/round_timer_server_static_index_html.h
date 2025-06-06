#include <Arduino.h>

const char round_timer_server_static_index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="index.js"></script>
        <script src="repository.js"></script>
        <link rel="stylesheet" href="style.css">
        <title>RoundTimer</title>
    </head>
    <body>

        <!-- main menu -->
        <div class="container hidden page" id="page-main-menu">

            <div class="mb-lg display-flex align-items-center">
                <h1>
                    RoundTimer
                </h1>
            </div>
        
            <div class="row">
                <div class="col col-4 col-sm-12 mb-lg-mobile">
                    <div class="card height-100">
                        <h2>Configuration</h2>
                        <p>Informations, réseau, sécurité</p>
                        <button class="primary mt-md" onclick="anchorLink('configuration')">
                            Configuration
                        </button>

                    </div>
                </div>

                <div class="col col-4 col-sm-12 mb-lg-mobile">
                    <div class="card height-100 elevation">
                        <h2>RoundTimer</h2>
                        <p>Contrôles du timer par réseau</p>
                        <button class="primary mt-md" onclick="anchorLink('round-timer')">
                            RoundTimer
                        </button>
                    </div>
                </div>

                <div class="col col-4 col-sm-12">
                    <div class="card height-100 elevation">
                        <h2>Lamp</h2>
                        <p>Lampe d'ambiance et presets</p>
                        <button class="primary mt-md" onclick="anchorLink('lamp')">
                            Lamp
                        </button>
                    </div>
                </div>
            </div>

        </div>

        
        <!-- configuration -->
        <div class="container hidden page" id="page-configuration">

            <div class="mb-lg display-flex align-items-center">
                <h1>
                    Configuration
                </h1>
            </div>
        
            <div class="row">

                <div class="col col-6 col-sm-12 mb-md-mobile">
                    <div class="card height-100 elevation block-configuraion-info">
                        <h2>Informations système</h2>
                        <p>Réseau WiFi: <strong class="value_sta_ssid">non connecté</strong></p>
                        <p>Adresse IP: <strong class="value_sta_ip">non connecté</strong></p>
                        <p>Domaine local: <strong class="value_mdns_host">non connecté</strong></p>
                        <p>Version firmware: <strong class="value_firmware_version">2.0</strong></p>
                    </div>
                </div>

                <div class="col col-6 col-sm-12">
                    <div class="card height-100 elevation bloc-wifi-credentials">
                        <h2>Connection WiFi</h2>
                        <h4 class="mb-md">
                            Entrez le nom du réseau et le mot de passe
                        </h4>
                        <input class="input-wifi-ssid" type="text" placeholder="Nom du réseau">

                        <input class="mt-md input-wifi-password" type="text" placeholder="Mot de passe">

                        <button class="primary mt-lg" onclick="saveWifiCredentials(this)">
                            Enregistrer
                        </button>
                    </div>
                </div>
            </div>

            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>RoundTimer Configuration</h2>
                                    
                        <button class="primary" onclick="anchorLink('round-timer-configurations')">
                            Configuration
                        </button>
                    </div>
                </div>
            </div>

            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-saved-files">
                        <h2>Personnalisations sauvegardées</h2>
                        
                        <h4>Pas de personnalisations sauvegardées. Tous les paramètres sont d'origine.</h4>

                        <ul class="list mt-lg hidden">
                            <li class="hidden list-item-sta-credentials">
                                <div class="content">
                                    <div class="title">Configuration du réseau wifi</div>
                                </div>
                                <div class="actions">
                                    <button class="accent" onclick="deleteStaCredentialsFile(this)">
                                        Supprimer
                                    </button>
                                </div>
                            </li>
                            <li class="hidden list-item-configurations">
                                <div class="content">
                                    <div class="title">Configuration du round timer</div>
                                </div>
                                <div class="actions">
                                    <button class="accent" onclick="deleteConfigurationsFile(this)">
                                        Supprimer
                                    </button>
                                </div>
                            </li>
                            <li class="hidden list-item-lamps-presets">
                                <div class="content">
                                    <div class="title">Configuration des presets de la lampe</div>
                                </div>
                                <div class="actions">
                                    <button class="accent" onclick="deleteLampsPresetsFile(this)">
                                        Supprimer
                                    </button>
                                </div>
                            </li>
                        </ul>                        
                    </div>
                </div>
            </div>

            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-firmware">
                        <h2>Mise a jour firmware</h2>
                        <div class="file-upload">
                            Chargez le fichier firmware
                            <input type='file' name='firmware' onchange="selectedFirmware()">
                        </div>
                        <h4 class="error-message mt-lg hidden"></h4>
                        <div>
                            <button class="write-firmware accent mt-lg hidden" onclick="updateFirmware(this)">
                                Ecrire le firmware selectionné
                            </button>
                        </div>
                    </div>
                </div>
            </div>

            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-security">
                        <h2>Sécurité</h2>
                        <div>
                            <input type="checkbox" id="block-security-desactivate-access-point" name="security_desactivate_access_point">
                            <label for="block-security-desactivate-access-point">Désactiver le point d'accès apres 15 minutes</label>
                        </div>
                        <div>
                            <button class="write-firmware accent mt-lg" onclick="updateAccessPointAutoDisable(this)">
                                Mettre à jour
                            </button>
                        </div>
                    </div>
                </div>
            </div>

            <button class="primary mt-lg" onclick="anchorLink('main-menu')">
                Menu principal
            </button>

        </div>


        <!-- RoundTimer -->
        <div class="container hidden page" id="page-round-timer">

            <div class="mb-lg display-flex align-items-center">
                <h1>
                    RoundTimer
                </h1>
            </div>
        
            <div class="row">
                <div class="col col-6 col-sm-12 mb-md-mobile">
                    <div class="card height-100 elevation block-round-timer-lamp-preview">
                        <h2>Etat des lampes</h2>
                        <div class="row mt-lg">
                            <div class="col col-4">
                                <div class="lamp-preview lamp-0"></div>
                            </div>
                            <div class="col col-4">
                                <div class="lamp-preview lamp-1"></div>
                            </div>
                            <div class="col col-4">
                                <div class="lamp-preview lamp-2"></div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col col-6 col-sm-12">
                    <div class="card height-100 elevation block-round-timer-controls">
                        <h2>Contrôles</h2>

                        <div>
                            <button
                                class="primary mt-md round_timer_state_is_running_false"
                                onclick="setControls({round_timer_state_is_running:false})"
                            >
                                Timer éteint
                            </button>
                            <button
                                class="disabled mt-md round_timer_state_is_running_true"
                                onclick="setControls({round_timer_state_is_running:true})"
                            >
                                Timer allumé
                            </button>
                        </div>

                        <div>
                            <button
                                class="mt-md round_timer_state_is_round_long_duration_false"
                                onclick="setControls({round_timer_state_is_round_long_duration:false})"
                            >
                                Round de 2min
                            </button>
                            <button
                                class="mt-md round_timer_state_is_round_long_duration_true" 
                                onclick="setControls({round_timer_state_is_round_long_duration:true})"
                            >
                                Round de 3min
                            </button>
                        </div>
                        <div>
                            <button
                                class="mt-md round_timer_state_is_rest_long_duration_false"
                                onclick="setControls({round_timer_state_is_rest_long_duration:false})"
                            >
                                Repos 30s
                            </button>
                            <button
                                class="mt-md round_timer_state_is_rest_long_duration_true"
                                onclick="setControls({round_timer_state_is_rest_long_duration:true})"
                            >
                                Repos 1min
                            </button>
                        </div>                        
                        <button class="primary mt-lg block" onclick="anchorLink('round-timer-configurations')">
                            Configuration timer
                        </button>
                    </div>
                </div>

            </div>

            <button class="primary mt-lg" onclick="anchorLink('main-menu')">
                Menu principal
            </button>

        </div>


        <!-- RoundTimerConfiguration -->
        <div class="container hidden page" id="page-round-timer-configurations">

            <div class="mb-lg display-flex align-items-center">
                <h1>
                    RoundTimer Configuration
                </h1>
            </div>
        
            <div class="row">
                <div class="col col-6 col-sm-12 mb-md-mobile">
                    <div class="card height-100 elevation block-round-timer-controls">
                        <h2>Mode des lampes</h2>
                        <div>
                            <div>
                                <input type="radio" id="round-timer-configuration-sequential-mode" name="round_timer_mode" value="1">
                                <label for="round-timer-configuration-sequential-mode">Lampes en mode séquentiel</label>
                            </div>
                            
                            <div class="mt-sm">
                                <input type="radio" id="round-timer-configuration-all-mode" name="round_timer_mode" value="2">
                                <label for="round-timer-configuration-all-mode">Toutes les lampes indiquent l'état</label>
                            </div>
                        </div>

                        <h2 class="mt-lg">Sens de la séquence</h2>
                        <div>
                            <div>
                                <input type="radio" id="round-timer-configuration-orientation-left" name="round_timer_sequential_mode_order" value="0">
                                <label for="round-timer-configuration-orientation-left">Début a gauche</label>
                            </div>
                            
                            <div class="mt-sm">
                                <input type="radio" id="round-timer-configuration-orientation-right" name="round_timer_sequential_mode_order" value="1">
                                <label for="round-timer-configuration-orientation-right">Début a droite</label>
                            </div>
                        </div>

                        <h2 class="mt-lg">Buzzer</h2>
                        <div>
                            <div>
                                <input type="checkbox" id="round-timer-configuration-mute" name="round_timer_mute">
                                <label for="round-timer-configuration-mute">Désactiver le son</label>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col col-6 col-sm-12 ">
                    <div class="card height-100 elevation block-round-timer-controls">

                        <h2>Configuration des couleurs</h2>
                        <div class="mb-sm">
                            <p>Couleur du round</p>
                            <input type="color" class="display-block lamp-set-round-color" name="round_timer_round_color">
                        </div>
                        <div class="mb-sm">
                            <p>Couleur du fin de round (prérepos)</p>
                            <input type="color" class="display-block lamp-set-round-color" name="round_timer_prerest_color">
                        </div>
                        <div>
                            <p>Couleur du repos</p>
                            <input type="color" class="display-block lamp-set-round-color" name="round_timer_rest_color">
                        </div>
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="col col-12 col-sm-12 mt-md">
                    <div class="card height-100 elevation block-round-timer-controls">
                        <h2>Configuration des temps</h2>

                        <div class="row">
                            <div class="col col-6 col-sm-12 mb-md-mobile">
                                <h4 class="mb-md">
                                    Durée du round courte (120 secondes par défaut)
                                </h4>
                                <input type="number" min="1" name="round_timer_round_short_duration">
                            </div>
                            <div class="col col-6 col-sm-12">
                                <h4 class="mb-md">
                                    Durée du round longue (180 secondes par défaut)
                                </h4>
                                <input type="number" min="1" name="round_timer_round_long_duration">
                            </div>
                        </div>

                        <div class="row mt-md">
                            <div class="col col-6 col-sm-12 mb-md-mobile">
                                <h4 class="mb-md">
                                    Durée du repos courte (30 secondes par défaut)
                                </h4>
                                <input type="number" min="1" name="round_timer_rest_short_duration">
                            </div>
                            <div class="col col-6 col-sm-12">
                                <h4 class="mb-md">
                                    Durée du repos longue (60 secondes par défaut)
                                </h4>
                                <input type="number" min="1" name="round_timer_rest_long_duration">
                            </div>
                        </div>
                        
                        <h4 class="mb-md mt-md">
                            Durée du prérepos (30 secondes par défaut)
                        </h4>
                        <input type="number" min="0" name="round_timer_prerest_duration">

                        <h4 class="mb-md mt-md">
                            Durée avant le premier round (5 secondes par défaut)
                        </h4>
                        <input type="number" min="1" name="round_timer_prestart_duration">

                    </div>
                </div>
            </div>

            <button class="primary mt-lg" onclick="anchorLink('main-menu')">
                Menu principal
            </button>

            <button class="primary mt-lg" onclick="saveRoundTimerConfiguration(this)">
                Sauvegarder
            </button>
            
        </div>


        <!-- Lamp -->
        <div class="container hidden page" id="page-lamp">

            <div class="mb-lg display-flex align-items-center">
                <h1>
                    Lamp
                </h1>
            </div>
        
            <div class="row">
                <div class="col col-6 col-sm-12 mb-md-mobile">
                    <div class="card height-100 elevation block-lamp-controls">
                        <h2>Etat des lampes</h2>
                        <div class="row mt-lg">
                            <div class="col col-4">
                                <input
                                    class="lamp-preview lamp-0 display-block"
                                    type="color"
                                    name="lamp_0_color"
                                    onchange="updateLampsColors()"
                                >
                            </div>
                            <div class="col col-4">
                                <input 
                                    class="lamp-preview lamp-1 display-block"
                                    type="color"
                                    name="lamp_1_color"
                                    onchange="updateLampsColors()"
                                >
                            </div>
                            <div class="col col-4">
                                <input
                                    class="lamp-preview lamp-2 display-block"
                                    type="color"
                                    name="lamp_2_color"
                                    onchange="updateLampsColors()"
                                >
                            </div>

                            
                                <button
                                    class="primary mt-md center"
                                    onclick="setLampColor({lamp_0_color:'#000000',lamp_1_color:'#000000',lamp_2_color:'#000000'})"
                                >
                                    Eteindre tous
                                </button>

                                <button
                                    class="accent mt-md center save-preset-button hidden"
                                    onclick="saveCurrentPreset(this)"
                                >
                                    Sauvegarder le preset
                                </button>
                        </div>
                    </div>
                </div>

                <div class="col col-6 col-sm-12">
                    <div class="card height-100 elevation block-lamp-presets">
                        <h2>Raccourcis couleurs</h2>
                        
                        <div class="row mt-lg color-presets">
                        </div>
                    </div>
                </div>

            </div>

            <button class="primary mt-lg" onclick="anchorLink('main-menu')">
                Menu principal
            </button>

        </div>

        <template id="template-color-preset">
            <div class="col col-2_4">
                <div class="preset-icon row center lamp-preset-index-{{ index }}" onclick="displayPresetColors('{{ color_0 }}', '{{ color_1 }}', '{{ color_2 }}', '{{ index }}')">
                    <div class="display-flex col-4 height-100 color_0"></div>
                    <div class="display-flex col-4 height-100 color_1"></div>
                    <div class="display-flex col-4 height-100 color_2"></div>
                </div>                            
            </div>
        </template>

    </body>
</html>
)rawliteral";

