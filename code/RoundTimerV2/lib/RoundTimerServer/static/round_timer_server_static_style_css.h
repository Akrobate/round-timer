#include <Arduino.h>

const char round_timer_server_static_style_css[] PROGMEM = R"rawliteral(
:root {

    --primary-color: #3498db;
    --secondary-color-1: #2ecc71;
    --secondary-color-2: #e67e22;
    --accent-color: #e74c3c;
    --neutral-color-1: #2c3e50;

    --neutral-color-2: #dce1e2;
    --neutral-color-3: #f9f9f9;

    --neutral-color-4: #ffffff;

    --margin-xs: 4px;
    --margin-sm: 8px;
    --margin-md: 16px;
    --margin-lg: 32px;
    --margin-xl: 64px;
}
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

.mt-xs { margin-top: var(--margin-xs); }
.mt-sm { margin-top: var(--margin-sm); }
.mt-md { margin-top: var(--margin-md); }
.mt-lg { margin-top: var(--margin-lg); }

.mb-xs { margin-bottom: var(--margin-xs); }
.mb-sm { margin-bottom: var(--margin-sm); }
.mb-md { margin-bottom: var(--margin-md); }
.mb-lg { margin-bottom: var(--margin-lg); }

.ml-xs { margin-left: var(--margin-xs); }
.ml-sm { margin-left: var(--margin-sm); }
.ml-md { margin-left: var(--margin-md); }
.ml-lg { margin-left: var(--margin-lg); }




body {
    background-color: var(--neutral-color-4);
    color: var(--neutral-color-1);
    font-family: Arial, sans-serif;
    font-family: Arial, sans-serif;
}

h1, h2, h3, h4, h5, h6 {
    color: var(--neutral-color-1);
}

h2 {
    margin-bottom: var(--margin-md);
}
h3 {
    margin-bottom: var(--margin-md);
}

p {
    margin-bottom: var(--margin-sm);
}

a {
    color: var(--primary-color);
    text-decoration: none;
}

a:hover {
    color: var(--secondary-color-1);
}

button, input[type="submit"] {
    background-color: var(--primary-color);
    color: var(--neutral-color-3);
    border: none;
    padding: 10px 15px;
    cursor: pointer;
    border-radius: 5px;
    font-weight: 500;
    font-size: 16px;
}

.file-upload {
    position: relative;
    display: inline-block;
    cursor: pointer;
    background-color: var(--primary-color);
    color: var(--neutral-color-3);
    padding: 10px 20px;
    border-radius: 5px;
    font-size: 16px;
    text-align: center;
}

.file-upload input[type="file"] {
    position: absolute;
    opacity: 0;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    cursor: pointer;
}


button.secondary {
    background-color: var(--secondary-color-1);
}

button.accent {
    background-color: var(--accent-color);
}

button:disabled,
button[disabled]{
  border: 1px solid #cccccc;
  background-color: #eeeeee;
  color: #666666;
}

button.icon:disabled,
button.icon[disabled]{
  border: 1px solid #cccccc;
  background-color: #eeeeee;
  color: #adadad;
}

button.icon {
    padding: 5px;
    color: var(--neutral-color-4);
}

button.icon svg {
    width: 27px;
    height: 27px;
}


.container {
    margin: var(--margin-lg) auto;
    padding: var(--margin-md);
    max-width: 960px;
}

.section {
    margin-bottom: var(--margin-xl);
}

.card {
    margin-bottom: var(--margin-md);
    padding: var(--margin-md);
    border: 1px solid var(--neutral-color-2);
    background-color: var(--neutral-color-3);
    border-radius: 4px;
}

.inner-card {
    margin-bottom: 0;
    padding: var(--margin-md);
    background-color: var(--neutral-color-4);
    border-radius: 4px;
}

.alert {
    background-color: var(--secondary-color-2);
    color: var(--neutral-color-3);
    padding: 10px;
    border-left: 5px solid var(--accent-color);
}

.row {
    display: flex;
    flex-wrap: wrap;
    margin-right: calc(var(--margin-sm) * -1);
    margin-left: calc(var(--margin-sm) * -1);
}
  
.col {
    flex: 1;
    padding-right: var(--margin-sm);
    padding-left: var(--margin-sm);
}

.display-flex {
    display: flex;
}

.align-items-center {
    align-items: center;
}

.col-1 { flex: 0 0 8.33%; }
.col-2 { flex: 0 0 16.66%; }
.col-3 { flex: 0 0 25%; }
.col-4 { flex: 0 0 33.33%; }
.col-5 { flex: 0 0 41.66%; }
.col-6 { flex: 0 0 50%; }
.col-7 { flex: 0 0 58.33%; }
.col-8 { flex: 0 0 66.66%; }
.col-9 { flex: 0 0 75%; }
.col-10 { flex: 0 0 83.33%; }
.col-11 { flex: 0 0 91.66%; }
.col-12 { flex: 0 0 100%; }

@media (max-width: 767px) {
    .col-sm-6 { flex: 0 0 50%;  }
    .col-sm-12 { flex: 0 0 100%; }

    .hide-mobile {
        display: none;
    }

    .mb-lg-mobile {
        margin-bottom: var(--margin-lg);
    }
}

.height-100 {
    height: 100%;
}

.elevation {
    box-shadow: 1px 2px 5px 1px rgba(0, 0, 0, 0.10);
}

ul.list {
    list-style: none;
    
}

ul.list li.list-item {
    margin-bottom: var(--margin-md);
    display: flex;
    justify-content: space-between;
}

ul.list .title {
    font-weight: bold;
    margin-bottom: var(--margin-sm);
}

ul.list .actions {   
    display: flex;
    justify-content: flex-end;
    align-items: center;    
}

ul.list button {
    margin-left: var(--margin-sm);
}

.debug {
    border: 1px solid red;
}

input[type="text"] {
    padding: 10px;
    border: 1px solid var(--neutral-color-2);
    border-radius: 4px;
    font-size: 16px;
    width: 100%;
    box-sizing: border-box;
}

select {
    padding: 10px;
    border: 1px solid var(--neutral-color-2);
    border-radius: 4px;
    font-size: 16px;
    width: 100%;
    box-sizing: border-box;
    background-color: #fff;
}

input.error {
    border: 1px solid var(--accent-color);
}

.loader {
    border: 10px solid #c5c2c2;
    border-top: 10px solid #3498db;
    border-radius: 50%;
    width: 50px;
    height: 50px;
    animation: spin 1s linear infinite;
}

.loader-small {
    border: 1px solid #c5c2c2;
    border-top: 1px solid #3498db;
    border-radius: 50%;
    width: 10px;
    height: 10px;
    animation: spin 1s linear infinite;
}

@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}

.center {
    margin-left: auto;
    margin-right: auto;
}

.hidden {
    display: none;
}

.logo {
    width: 60px;
    height: 40px;
    fill: var(--primary-color);
}

#available-networks-list {
    overflow-y: scroll;
    max-height: 200px;
    padding-right: 10px;
}

#available-networks-list::-webkit-scrollbar {
    width: 7px;
}

#available-networks-list::-webkit-scrollbar-track {
    box-shadow: inset 0 0 5px var(--neutral-color-4);
    border-radius: 10px;
}

#available-networks-list::-webkit-scrollbar-thumb {
    background: var(--neutral-color-2);
    border-radius: 10px;
}
)rawliteral";
