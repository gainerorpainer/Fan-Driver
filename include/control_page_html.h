#pragma once
const char * CONTROL_PAGE_HTML =
"<!doctype html>"
"<html lang=\"en\">"
""
"<head>"
"    <meta charset=\"utf-8\">"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
"    <title>Fan Driver Control</title>"
"    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css\" rel=\"stylesheet\""
"        integrity=\"sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD\" crossorigin=\"anonymous\">"
""
"    <style type=\"text/css\">"
"        .blockDiv {"
"            position: absolute;"
"            top: 0px;"
"            left: 0px;"
"            background-color: #FFF;"
"            width: 0px;"
"            height: 0px;"
"            z-index: 10;"
"            opacity: 0.7;"
"        }"
""
"        .blockP {"
"            margin-left: 50%;"
"            margin-top: 50%;"
"            font-size: xx-large;"
"        }"
""
"        svg {"
"            margin-bottom: 6px;"
"        }"
"    </style>"
""
"</head>"
""
"<body>"
"    <h1>Fan Driver Control</h1>"
""
"    <div class=\"container\">"
"        <!--TOPs-->"
"        <div class=\"mb-3\">"
"            <div class=\"row\">"
"                <div class=\"col\">"
"                    <input class=\"form-check-input\" type=\"checkbox\" value=\"\" id=\"isConnected\" checked>"
"                    <label class=\"form-check-label\" for=\"isConnected\">"
"                        Verbindung hergestellt"
"                    </label>"
"                </div>"
"                <div class=\"col\">"
"                    <button class=\"btn btn-primary\" onclick=\"refresh()\">Werte aktualisieren</button>"
"                </div>"
"            </div>"
""
"        </div>"
""
"        <br />"
"        <hr />"
"        <br />"
""
"        <!--STATUS-->"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"red\" class=\"bi bi-thermometer-half\""
"            viewBox=\"0 0 16 16\">"
"            <path d=\"M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z\" />"
"            <path"
"                d=\"M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z\" />"
"        </svg>"
"        <div class=\"mb-3\">"
"            <div class=\"row\">"
"                <div class=\"col\">"
"                    <label for=\"heaterTemp\" class=\"form-label\">Heizungstemperatur:</label>"
"                    <input class=\"form-control\" id=\"heaterTemp\" type=\"text\" placeholder=\"Warte auf Daten...\" disabled>"
"                </div>"
"                <div class=\"col\">"
"                    <label for=\"roomTemp\" class=\"form-label\">Raumtemperatur:</label>"
"                    <input class=\"form-control\" id=\"roomTemp\" type=\"text\" placeholder=\"Warte auf Daten...\" disabled>"
"                </div>"
"            </div>"
""
"        </div>"
""
"        <br />"
"        <hr />"
"        <br />"
""
"        <!--MANUAL POWER-->"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"blue\" class=\"bi bi-fan\""
"            viewBox=\"0 0 16 16\">"
"            <path"
"                d=\"M10 3c0 1.313-.304 2.508-.8 3.4a1.991 1.991 0 0 0-1.484-.38c-.28-.982-.91-2.04-1.838-2.969a8.368 8.368 0 0 0-.491-.454A5.976 5.976 0 0 1 8 2c.691 0 1.355.117 1.973.332.018.219.027.442.027.668Zm0 5c0 .073-.004.146-.012.217 1.018-.019 2.2-.353 3.331-1.006a8.39 8.39 0 0 0 .57-.361 6.004 6.004 0 0 0-2.53-3.823 9.02 9.02 0 0 1-.145.64c-.34 1.269-.944 2.346-1.656 3.079.277.343.442.78.442 1.254Zm-.137.728a2.007 2.007 0 0 1-1.07 1.109c.525.87 1.405 1.725 2.535 2.377.2.116.402.222.605.317a5.986 5.986 0 0 0 2.053-4.111c-.208.073-.421.14-.641.199-1.264.339-2.493.356-3.482.11ZM8 10c-.45 0-.866-.149-1.2-.4-.494.89-.796 2.082-.796 3.391 0 .23.01.457.027.678A5.99 5.99 0 0 0 8 14c.94 0 1.83-.216 2.623-.602a8.359 8.359 0 0 1-.497-.458c-.925-.926-1.555-1.981-1.836-2.96-.094.013-.191.02-.29.02ZM6 8c0-.08.005-.16.014-.239-1.02.017-2.205.351-3.34 1.007a8.366 8.366 0 0 0-.568.359 6.003 6.003 0 0 0 2.525 3.839 8.37 8.37 0 0 1 .148-.653c.34-1.267.94-2.342 1.65-3.075A1.988 1.988 0 0 1 6 8Zm-3.347-.632c1.267-.34 2.498-.355 3.488-.107.196-.494.583-.89 1.07-1.1-.524-.874-1.406-1.733-2.541-2.388a8.363 8.363 0 0 0-.594-.312 5.987 5.987 0 0 0-2.06 4.106c.206-.074.418-.14.637-.199ZM8 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2Z\" />"
"            <path d=\"M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14Zm0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16Z\" />"
"        </svg>"
"        <div class=\"mb-3\">"
"            <div class=\"row\">"
"                <div class=\"col-8\">"
"                    <label for=\"roomTemp\" class=\"form-label\">Manuell eingestellte Leistung:</label>"
"                    <input class=\"form-control\" id=\"manualPowerPerc\" type=\"range\" min=\"1\" max=\"100\" value=\"0\""
"                        onchange=\"SetManualPower(this.value)\">"
"                </div>"
"                <div class=\"col-4\">"
"                    <label for=\"roomTemp\" class=\"form-label\">Manuelle Steuerung aktiv für:</label>"
"                    <input class=\"form-control\" id=\"manualSecondsLeft\" type=\"text\" placeholder=\"Warte auf Daten...\""
"                        disabled>"
"                </div>"
""
"            </div>"
""
"        </div>"
""
"        <br />"
"        <hr />"
"        <br />"
""
"        <!-- PARAMETERS -->"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"grey\" class=\"bi bi-sliders\""
"            viewBox=\"0 0 16 16\">"
"            <path fill-rule=\"evenodd\""
"                d=\"M11.5 2a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zM9.05 3a2.5 2.5 0 0 1 4.9 0H16v1h-2.05a2.5 2.5 0 0 1-4.9 0H0V3h9.05zM4.5 7a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zM2.05 8a2.5 2.5 0 0 1 4.9 0H16v1H6.95a2.5 2.5 0 0 1-4.9 0H0V8h2.05zm9.45 4a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zm-2.45 1a2.5 2.5 0 0 1 4.9 0H16v1h-2.05a2.5 2.5 0 0 1-4.9 0H0v-1h9.05z\" />"
"        </svg>"
"        <div class=\"mb-3\">"
"            <div class=\"row\">"
"                <div class=\"col\">"
"                    <label for=\"pMin\" class=\"form-label\">Leistungsuntergrenze bevor Lüfter stehen bleiben:</label>"
"                    <input class=\"form-control\" id=\"pMin\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" disabled>"
"                </div>"
""
"                <div class=\"col\">"
"                    <label for=\"pMax\" class=\"form-label\">Akzeptable Leistungsobergrenze:</label>"
"                    <input class=\"form-control\" id=\"pMax\" type=\"range\" min=\"0\" max=\"255\" value=\"255\" step=\"1\">"
"                </div>"
""
"                <div class=\"col\">"
"                    <label for=\"tRoomMin\" class=\"form-label\">Zu erreichende Raumtemperatur:</label>"
"                    <input class=\"form-control\" id=\"tRoomMin\" type=\"number\" min=\"0\" max=\"30\" placeholder=\"z.B. 22.0 °C\">"
"                </div>"
""
"                <div class=\"col\">"
"                    <label for=\"tHeatMin\" class=\"form-label\">Minimale Heizungstemperatur um aktiv zu sein:</label>"
"                    <input class=\"form-control\" id=\"tHeatMin\" type=\"number\" min=\"20\" max=\"60\" placeholder=\"z.B. 30.0 °C\""
"                        step=\"0.1\">"
"                </div>"
""
"                <div class=\"col\">"
"                    <label for=\"hostName\" class=\"form-label\">Hostname im WLAN (max. 15 Zeichen!):</label>"
"                    <input class=\"form-control\" id=\"hostName\" type=\"text\" maxlength=\"15\""
"                        placeholder=\"Wohnzimmer, Büro, etc...\">"
"                </div>"
"            </div>"
""
"            <br />"
""
"            <div class=\"row\">"
"                <button class=\"btn btn-secondary\" onclick=\"postParameters()\">Parameter speichern</button>"
"            </div>"
"        </div>"
"    </div>"
""
"    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js\""
"        integrity=\"sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN\" crossorigin=\"anonymous\">"
"        </script>"
"    <script src=\"https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.3.min.js\">"
"    </script>"
""
"    <script>"
""
"        function _lock_screen() {"
"            $('<div id=\"screenBlock\" class=\"blockDiv\"><p class=\"blockP\">Lade...</p></div>').appendTo('body');"
"            $('#screenBlock').css({ width: $(document).width(), height: $(document).height() });"
"        }"
""
"        function _unlock_screen() {"
"            $('#screenBlock').remove();"
"        }"
""
"        function _refreshParameters() {"
"            $.get(\"/parameters\", function (data, status) {"
"                $('#pMin').val(data.pMin);"
"                $('#pMax').val(data.pMax);"
"                $('#tRoomMin').val(data.tRoomMin);"
"                $('#tHeatMin').val(data.tHeatMin);"
"                $('#hostName').val(data.hostName);"
"            })"
"                .done(function () { _unlock_screen(); });"
"        }"
""
"        function refresh() {"
"            _lock_screen();"
"            $.get(\"/status\", function (data, status) {"
"                $('#heaterTemp').val(data.heaterTemp);"
"                $('#roomTemp').val(data.roomTemp);"
"                $('#roomTemp').val(data.roomTemp);"
"            })"
"                .done(function () { _refreshParameters(); });"
"        }"
""
"        function postParameters() {"
"            _lock_screen();"
"            var parameters = {"
"                pMin: $('#pMin').val(),"
"                pMax: $('#pMax').val(),"
"                tRoomMin: $('#tRoomMin').val(),"
"                tHeatMin: $('#tHeatMin').val(),"
"                hostName: $('#hostName').val()"
"            };"
"            $.post(\"/parameters\", { parameters: JSON.stringify(parameters) })"
"                .done(function () { _unlock_screen(); });"
"        }"
""
"        function SetManualPower(percent) {"
"            _lock_screen();"
"            $.post(\"/manualPower\", { percent: percent })"
"                .done(function () { _unlock_screen(); refresh(); });"
"        }"
"    </script>"
"</body>"
""
"</html"
;
