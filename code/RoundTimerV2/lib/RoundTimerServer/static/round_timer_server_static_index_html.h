#include <Arduino.h>

const char round_timer_server_static_index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="index.js"></script>
        <script src="mock-server.js"></script>
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
                    <div class="card height-100 elevation block-info-primary">
                        <h2>Configuration</h2>
                        <p>Stream</p>
                        <button class="primary mt-md" onclick="anchorLink('configuration')">
                            Configuration
                        </button>

                    </div>
                </div>

                <div class="col col-4 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>RoundTimer</h2>
                        <p>Stream</p>
                        <button class="primary mt-md" onclick="refreshInfo(this)">
                            RoundTimer
                        </button>
                    </div>
                </div>

                <div class="col col-4 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>Lamp</h2>
                        <p>Stream</p>
                        <button class="primary mt-md" onclick="refreshInfo(this)">
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

                <div class="col col-6 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>Informations système</h2>
                        <p>Réseau WiFi: <strong>non connecté</strong></p>
                        <p>Adresse IP: <strong>non connecté</strong></p>
                        <p>Domaine local: <strong>non connecté</strong></p>
                        <p>Version firmware: <strong>2.0</strong></p>
                    </div>
                </div>

                <div class="col col-6 col-sm-12 mb-lg-mobile">
                    <div class="card height-100 elevation block-info-primary">
                        <h2>Connection WiFi</h2>
                        <div class="">
                            <h4 class="mb-md">
                                Entrez le nom du réseau et le mot de passe
                            </h4>
                            <input type="text" id="input-ssid-name" placeholder="SSID">
                            <input class="mt-md" id="input-ssid-password" type="text" placeholder="Password">
    
                            <button class="secondary mt-lg" onclick="resetCreatingSavedWifi()">
                                Cancel
                            </button>
    
                            <button class="primary mt-lg" onclick="saveNetwork(this)">
                                Save
                            </button>
                        </div>

                    </div>
                </div>

            </div>
            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>Mise a jour firmware</h2>
                        <form method='POST' action='/update' enctype='multipart/form-data'>
                            <div class="file-upload">
                                Chargez le fichier firmware
                                <input type='file' name='firmware'>
                            </div>
                            <input type='submit' value='Ecrire le firmware selectionné'>
                          </form>
                    </div>
                </div>
            </div>

            <div class="row mt-md">
                <div class="col col-12 col-sm-12">
                    <div class="card height-100 elevation block-info-secondary">
                        <h2>Sécurité</h2>
                    </div>
                </div>
            </div>

            <button class="primary mt-lg" onclick="anchorLink('main-menu')">
                Menu principal
            </button>

        </div>


    </body>
</html>
)rawliteral";

