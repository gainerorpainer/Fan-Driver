#pragma once

#include <Arduino.h>

static const char STATIC_HTML_MAINPAGE[] ICACHE_RODATA_ATTR =
"<!doctype html>\r\n"
"<html lang=\"en\">\r\n"
"\r\n"
"<head>\r\n"
"    <meta charset=\"utf-8\">\r\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n"
"    <title>Fan Driver Controller</title>\r\n"
"    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css\" rel=\"stylesheet\"\r\n"
"        integrity=\"sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD\" crossorigin=\"anonymous\">\r\n"
"\r\n"
"    <style type=\"text/css\">\r\n"
"        .blockDiv {\r\n"
"            position: absolute;\r\n"
"            top: 0px;\r\n"
"            left: 0px;\r\n"
"            background-color: #FFF;\r\n"
"            width: 0px;\r\n"
"            height: 0px;\r\n"
"            z-index: 10;\r\n"
"            opacity: 0.7;\r\n"
"        }\r\n"
"\r\n"
"        input[type=text],\r\n"
"        input[type=number] {\r\n"
"            text-align: end;\r\n"
"        }\r\n"
"\r\n"
"        .blockP {\r\n"
"            margin-left: 50%;\r\n"
"            margin-top: 50%;\r\n"
"            font-size: xx-large;\r\n"
"        }\r\n"
"\r\n"
"        svg {\r\n"
"            margin-bottom: 6px;\r\n"
"        }\r\n"
"\r\n"
"        h1 {\r\n"
"            text-align: center;\r\n"
"        }\r\n"
"    </style>\r\n"
"\r\n"
"</head>\r\n"
"\r\n"
"<body>\r\n"
"    <h1>Fan Driver Controller</h1>\r\n"
"\r\n"
"    <div class=\"container\">\r\n"
"        <!--TOPs-->\r\n"
"        <div class=\"mb-3\">\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col-2\">\r\n"
"                    <input class=\"form-check-input\" type=\"checkbox\" value=\"\" id=\"isConnected\" checked>\r\n"
"                    <label class=\"form-check-label\" for=\"isConnected\">\r\n"
"                        Verbindung hergestellt\r\n"
"                    </label>\r\n"
"                </div>\r\n"
"                <div class=\"col-3\">\r\n"
"                    <label for=\"upTimeSeconds\" class=\"form-label\">System aktiv seit:</label>\r\n"
"                    <input type=\"text\" id=\"upTimeSeconds\" size=\"10\" placeholder=\"...\" disabled /> s\r\n"
"                </div>\r\n"
"            </div>\r\n"
"        </div>\r\n"
"\r\n"
"        <br />\r\n"
"        <hr />\r\n"
"        <br />\r\n"
"\r\n"
"        <!--GRAPH-->\r\n"
"        <div>\r\n"
"            <canvas id=\"myChart\"></canvas>\r\n"
"        </div>\r\n"
"\r\n"
"        <br />\r\n"
"        <hr />\r\n"
"        <br />\r\n"
"\r\n"
"        <!--STATUS-->\r\n"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"red\" class=\"bi bi-thermometer-half\"\r\n"
"            viewBox=\"0 0 16 16\">\r\n"
"            <path d=\"M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z\" />\r\n"
"            <path\r\n"
"                d=\"M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z\" />\r\n"
"        </svg>\r\n"
"        <div class=\"mb-3\">\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col-4\">\r\n"
"                    <label for=\"roomTemp\" class=\"form-label\">Raumtemperatur:</label>\r\n"
"                    <input type=\"text\" id=\"roomTemp\" size=\"3\" placeholder=\"...\" disabled /> °C\r\n"
"                </div>\r\n"
"                <div class=\"col-4\">\r\n"
"                    <label for=\"heaterTemp\" class=\"form-label\">Heizungstemperatur:</label>\r\n"
"                    <input type=\"text\" id=\"heaterTemp\" size=\"3\" placeholder=\"...\" disabled /> °C\r\n"
"                </div>\r\n"
"            </div>\r\n"
"\r\n"
"        </div>\r\n"
"\r\n"
"        <br />\r\n"
"        <hr />\r\n"
"        <br />\r\n"
"\r\n"
"        <!--FAN POWER-->\r\n"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"blue\" class=\"bi bi-fan\"\r\n"
"            viewBox=\"0 0 16 16\">\r\n"
"            <path\r\n"
"                d=\"M10 3c0 1.313-.304 2.508-.8 3.4a1.991 1.991 0 0 0-1.484-.38c-.28-.982-.91-2.04-1.838-2.969a8.368 8.368 0 0 0-.491-.454A5.976 5.976 0 0 1 8 2c.691 0 1.355.117 1.973.332.018.219.027.442.027.668Zm0 5c0 .073-.004.146-.012.217 1.018-.019 2.2-.353 3.331-1.006a8.39 8.39 0 0 0 .57-.361 6.004 6.004 0 0 0-2.53-3.823 9.02 9.02 0 0 1-.145.64c-.34 1.269-.944 2.346-1.656 3.079.277.343.442.78.442 1.254Zm-.137.728a2.007 2.007 0 0 1-1.07 1.109c.525.87 1.405 1.725 2.535 2.377.2.116.402.222.605.317a5.986 5.986 0 0 0 2.053-4.111c-.208.073-.421.14-.641.199-1.264.339-2.493.356-3.482.11ZM8 10c-.45 0-.866-.149-1.2-.4-.494.89-.796 2.082-.796 3.391 0 .23.01.457.027.678A5.99 5.99 0 0 0 8 14c.94 0 1.83-.216 2.623-.602a8.359 8.359 0 0 1-.497-.458c-.925-.926-1.555-1.981-1.836-2.96-.094.013-.191.02-.29.02ZM6 8c0-.08.005-.16.014-.239-1.02.017-2.205.351-3.34 1.007a8.366 8.366 0 0 0-.568.359 6.003 6.003 0 0 0 2.525 3.839 8.37 8.37 0 0 1 .148-.653c.34-1.267.94-2.342 1.65-3.075A1.988 1.988 0 0 1 6 8Zm-3.347-.632c1.267-.34 2.498-.355 3.488-.107.196-.494.583-.89 1.07-1.1-.524-.874-1.406-1.733-2.541-2.388a8.363 8.363 0 0 0-.594-.312 5.987 5.987 0 0 0-2.06 4.106c.206-.074.418-.14.637-.199ZM8 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2Z\" />\r\n"
"            <path d=\"M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14Zm0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16Z\" />\r\n"
"        </svg>\r\n"
"        <div class=\"mb-3\">\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col-6\">\r\n"
"                    <div class=\"row\">\r\n"
"                        <label for=\"currentPowerPerc\" class=\"form-label\">Aktuelle Lüfterleistung:</label>\r\n"
"                    </div>\r\n"
"                    <div class=\"row\">\r\n"
"                        <div class=\"col-4\">\r\n"
"                            <input class=\"form-control\" id=\"currentPowerPerc\" type=\"range\" min=\"0\" max=\"100\" value=\"0\"\r\n"
"                                disabled>\r\n"
"                        </div>\r\n"
"                        <div class=\"col-4\">\r\n"
"                            <input type=\"text\" id=\"currentPowerPerc_label\" size=\"3\" placeholder=\"...\" disabled /> %\r\n"
"                        </div>\r\n"
"                        <div class=\"col-4\">\r\n"
"                            <input type=\"text\" id=\"currentPowerPwm\" size=\"3\" placeholder=\"...\" disabled /> / 255\r\n"
"                        </div>\r\n"
"                    </div>\r\n"
"                </div>\r\n"
"            </div>\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col-6\">\r\n"
"                    <hr />\r\n"
"                </div>\r\n"
"            </div>\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col-2\">\r\n"
"                    <label for=\"manualPowerPerc\" class=\"form-label\">Manuell eingestellte Leistung:</label>\r\n"
"                    <input class=\"form-control\" id=\"manualPowerPerc\" type=\"range\" min=\"1\" max=\"100\" value=\"0\"\r\n"
"                        onchange=\"SetManualPower(this.value)\">\r\n"
"                </div>\r\n"
"                <div class=\"col-2\">\r\n"
"                    <label for=\"manualSecondsLeft\" class=\"form-label\">Manuelle Steuerung aktiv für:</label>\r\n"
"                    <input type=\"text\" id=\"manualSecondsLeft\" size=\"3\" placeholder=\"...\" disabled /> s\r\n"
"                </div>\r\n"
"\r\n"
"            </div>\r\n"
"\r\n"
"        </div>\r\n"
"\r\n"
"        <br />\r\n"
"        <hr />\r\n"
"        <br />\r\n"
"\r\n"
"        <!-- PARAMETERS -->\r\n"
"        <svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"grey\" class=\"bi bi-sliders\"\r\n"
"            viewBox=\"0 0 16 16\">\r\n"
"            <path fill-rule=\"evenodd\"\r\n"
"                d=\"M11.5 2a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zM9.05 3a2.5 2.5 0 0 1 4.9 0H16v1h-2.05a2.5 2.5 0 0 1-4.9 0H0V3h9.05zM4.5 7a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zM2.05 8a2.5 2.5 0 0 1 4.9 0H16v1H6.95a2.5 2.5 0 0 1-4.9 0H0V8h2.05zm9.45 4a1.5 1.5 0 1 0 0 3 1.5 1.5 0 0 0 0-3zm-2.45 1a2.5 2.5 0 0 1 4.9 0H16v1h-2.05a2.5 2.5 0 0 1-4.9 0H0v-1h9.05z\" />\r\n"
"        </svg>\r\n"
"        <div class=\"mb-3\">\r\n"
"            <div class=\"row\">\r\n"
"                <div class=\"col\">\r\n"
"                    <label for=\"pMin\" class=\"form-label\">Leistungsuntergrenze bevor Lüfter stehen bleiben:</label>\r\n"
"                    <input class=\"form-control\" id=\"pMin\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" disabled>\r\n"
"                </div>\r\n"
"\r\n"
"                <div class=\"col\">\r\n"
"                    <label for=\"pMax\" class=\"form-label\">Akzeptable Leistungsobergrenze:</label>\r\n"
"                    <input class=\"form-control\" id=\"pMax\" type=\"range\" min=\"0\" max=\"255\" value=\"255\" step=\"1\">\r\n"
"                </div>\r\n"
"\r\n"
"                <div class=\"col\">\r\n"
"                    <label for=\"tRoomMin\" class=\"form-label\">Zu erreichende Raumtemperatur:</label>\r\n"
"                    <input class=\"form-control\" id=\"tRoomMin\" type=\"number\" min=\"0\" max=\"30\" placeholder=\"z.B. 22.0 °C\">\r\n"
"                </div>\r\n"
"\r\n"
"                <div class=\"col\">\r\n"
"                    <label for=\"tHeatMin\" class=\"form-label\">Minimale Heizungstemperatur um aktiv zu sein:</label>\r\n"
"                    <input class=\"form-control\" id=\"tHeatMin\" type=\"number\" min=\"20\" max=\"60\" placeholder=\"z.B. 30.0 °C\"\r\n"
"                        step=\"0.1\">\r\n"
"                </div>\r\n"
"\r\n"
"                <div class=\"col\">\r\n"
"                    <label for=\"hostName\" class=\"form-label\">Hostname im WLAN (max. 15 Zeichen!):</label>\r\n"
"                    <input class=\"form-control\" id=\"hostName\" type=\"text\" maxlength=\"15\"\r\n"
"                        placeholder=\"Wohnzimmer, Büro, etc...\">\r\n"
"                </div>\r\n"
"            </div>\r\n"
"\r\n"
"            <br />\r\n"
"\r\n"
"            <div class=\"row\">\r\n"
"                <button class=\"btn btn-secondary\" onclick=\"postParameters()\">Parameter speichern</button>\r\n"
"            </div>\r\n"
"        </div>\r\n"
"    </div>\r\n"
"\r\n"
"    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js\"\r\n"
"        integrity=\"sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN\" crossorigin=\"anonymous\">\r\n"
"        </script>\r\n"
"    <script src=\"https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.3.min.js\">\r\n"
"    </script>\r\n"
"\r\n"
"    <script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\r\n"
"    <script\r\n"
"        src=\"https://cdnjs.cloudflare.com/ajax/libs/chartjs-plugin-annotation/2.1.1/chartjs-plugin-annotation.min.js\"></script>\r\n"
"\r\n"
"    <script>\r\n"
"        const ctx = document.getElementById(\"myChart\");\r\n"
"\r\n"
"        const data = {\r\n"
"            datasets: [\r\n"
"                {\r\n"
"                    label: \"Aktuelle Situation\",\r\n"
"                    borderColor: \"rgba(0,0,0)\",\r\n"
"                    pointBorderColor: \"rgba(0,0,0)\",\r\n"
"                    backgroundColor: \"rgba(0,0,0)\",\r\n"
"                    radius: 12,\r\n"
"                    pointStyle: \"circle\",\r\n"
"                    data: [\r\n"
"                        {\r\n"
"                            x: 0,\r\n"
"                            y: 0,\r\n"
"                        },\r\n"
"                    ],\r\n"
"                    backgroundColor: \"rgb(255, 99, 132)\",\r\n"
"                },\r\n"
"            ],\r\n"
"        };\r\n"
"\r\n"
"        const x_min = 10;\r\n"
"        const y_max = 10;\r\n"
"\r\n"
"        const annotations = {\r\n"
"            warmRoom: {\r\n"
"                type: \"box\",\r\n"
"                backgroundColor: \"rgba(255, 100, 100, 0.25)\",\r\n"
"                borderWidth: 0,\r\n"
"                xMin: x_min,\r\n"
"                yMin: y_max,\r\n"
"                label: {\r\n"
"                    display: true,\r\n"
"                    textAlign: \"center\",\r\n"
"                    content: [\"0%:\", \"warmer Raum\"],\r\n"
"                    position: { x: \"center\", y: \"center\" },\r\n"
"                    color: \"rgba(255, 100, 100)\",\r\n"
"                },\r\n"
"            },\r\n"
"\r\n"
"            coldHeater: {\r\n"
"                type: \"box\",\r\n"
"                backgroundColor: \"rgba(100, 100, 100, 0.25)\",\r\n"
"                borderWidth: 0.25,\r\n"
"                yMax: y_max,\r\n"
"                label: {\r\n"
"                    display: true,\r\n"
"                    textAlign: \"center\",\r\n"
"                    content: [\"0%:\", \"Heizkörper zu kalt\"],\r\n"
"                    color: \"rgba(100, 100, 100)\",\r\n"
"                },\r\n"
"            },\r\n"
"\r\n"
"            controlBox: {\r\n"
"                type: \"box\",\r\n"
"                backgroundColor: \"rgba(255, 120, 0, 0.25)\",\r\n"
"                borderWidth: 0,\r\n"
"                xMin: x_min - 1,\r\n"
"                xMax: x_min,\r\n"
"                yMin: y_max,\r\n"
"                label: {\r\n"
"                    display: true,\r\n"
"                    textAlign: \"center\",\r\n"
"                    content: [\"100% - 0%\", \"Regelung\"],\r\n"
"                    color: \"rgba(255, 120, 0)\",\r\n"
"                },\r\n"
"            },\r\n"
"\r\n"
"            fullPowerBox: {\r\n"
"                type: \"box\",\r\n"
"                backgroundColor: \"rgba(0, 0, 255, 0.25)\",\r\n"
"                borderWidth: 0,\r\n"
"                xMax: x_min - 1,\r\n"
"                yMin: y_max,\r\n"
"                label: {\r\n"
"                    display: true,\r\n"
"                    textAlign: \"center\",\r\n"
"                    content: [\"100%:\", \"kalter Raum\"],\r\n"
"                    color: \"rgba(0, 0, 255)\",\r\n"
"                },\r\n"
"            },\r\n"
"        };\r\n"
"\r\n"
"        chart = new Chart(ctx, {\r\n"
"            type: \"scatter\",\r\n"
"            options: {\r\n"
"                scales: {\r\n"
"                    x: {\r\n"
"                        suggestedMin: 15,\r\n"
"                        suggestedMax: 24,\r\n"
"                        title: {\r\n"
"                            display: true,\r\n"
"                            text: \"Raum [°C]\",\r\n"
"                        },\r\n"
"                    },\r\n"
"                    y: {\r\n"
"                        suggestedMin: 15,\r\n"
"                        suggestedMax: 50,\r\n"
"                        title: {\r\n"
"                            display: true,\r\n"
"                            text: \"Heizkörper [°C]\",\r\n"
"                        },\r\n"
"                    },\r\n"
"                },\r\n"
"                responsive: true,\r\n"
"                plugins: {\r\n"
"                    legend: {\r\n"
"                        position: \"top\",\r\n"
"                        labels: {\r\n"
"                            usePointStyle: true,\r\n"
"                        },\r\n"
"                    },\r\n"
"                    title: {\r\n"
"                        display: true,\r\n"
"                        text: \"Dashboard\",\r\n"
"                    },\r\n"
"                    annotation: {\r\n"
"                        annotations: annotations,\r\n"
"                    },\r\n"
"                },\r\n"
"            },\r\n"
"            data: data,\r\n"
"        });\r\n"
"\r\n"
"        /// @brief Updates Graph with new values, while @ the same time \r\n"
"        function UpdateGraph(status, parameters) {\r\n"
"\r\n"
"            if (status != null) {\r\n"
"                datapoint = chart.data.datasets[0].data[0];\r\n"
"\r\n"
"                datapoint.x = status.roomTemp;\r\n"
"                datapoint.y = status.heaterTemp;\r\n"
"            }\r\n"
"\r\n"
"            if (parameters != null) {\r\n"
"                controlXMin = parameters.tRoomMin - 1;\r\n"
"\r\n"
"                annotations.warmRoom.xMin = annotations.controlBox.xMax = parameters.tRoomMin;\r\n"
"                annotations.controlBox.xMin = annotations.fullPowerBox.xMax = controlXMin;\r\n"
"                annotations.coldHeater.yMax = annotations.warmRoom.yMin = annotations.controlBox.yMin = annotations.fullPowerBox.yMin = parameters.tHeatMin;\r\n"
"            }\r\n"
"\r\n"
"            chart.update();\r\n"
"        }\r\n"
"    </script>\r\n"
"\r\n"
"    <script>\r\n"
"\r\n"
"        function _lock_screen() {\r\n"
"            $('<div id=\"screenBlock\" class=\"blockDiv\"><p class=\"blockP\">Lade...</p></div>').appendTo('body');\r\n"
"            $('#screenBlock').css({ width: $(document).width(), height: $(document).height() });\r\n"
"        }\r\n"
"\r\n"
"        function _unlock_screen() {\r\n"
"            $('#screenBlock').remove();\r\n"
"        }\r\n"
"\r\n"
"        function _refreshParameters(lockScreen) {\r\n"
"            $.get(\"/parameters\", function (data, status) {\r\n"
"                $('#pMin').val(data.pMin);\r\n"
"                $('#pMax').val(data.pMax);\r\n"
"                $('#tRoomMin').val(data.tRoomMin);\r\n"
"                $('#tHeatMin').val(data.tHeatMin);\r\n"
"                $('#hostName').val(data.hostName);\r\n"
"\r\n"
"                UpdateGraph(null, data);\r\n"
"            })\r\n"
"                .done(function () {\r\n"
"                    if (lockScreen) {\r\n"
"                        _unlock_screen();\r\n"
"                    }\r\n"
"                });\r\n"
"        }\r\n"
"\r\n"
"        function refresh(lockScreen = false) {\r\n"
"            if (lockScreen) {\r\n"
"                _lock_screen();\r\n"
"            }\r\n"
"\r\n"
"            $.get(\"/status\", function (data, status) {\r\n"
"                $('#heaterTemp').val(data.heaterTemp?.toFixed(1) ?? \"nan\");\r\n"
"                $('#roomTemp').val(data.roomTemp?.toFixed(1) ?? \"nan\");\r\n"
"                $('#currentPowerPwm').val(data.currentPowerPwm);\r\n"
"                $('#currentPowerPerc, #currentPowerPerc_label').val(data.currentPowerPerc);\r\n"
"                $('#manualPowerPerc').val(data.manualPowerPerc);\r\n"
"                $('#manualSecondsLeft').val(data.manualSecondsLeft);\r\n"
"                $('#upTimeSeconds').val(data.upTimeSeconds);\r\n"
"\r\n"
"                UpdateGraph(data, null);\r\n"
"            })\r\n"
"                .done(function () {\r\n"
"                    _refreshParameters(lockScreen);\r\n"
"                });\r\n"
"        }\r\n"
"\r\n"
"        function postParameters() {\r\n"
"            _lock_screen();\r\n"
"            var parameters = {\r\n"
"                pMin: $('#pMin').val(),\r\n"
"                pMax: $('#pMax').val(),\r\n"
"                tRoomMin: $('#tRoomMin').val(),\r\n"
"                tHeatMin: $('#tHeatMin').val(),\r\n"
"                hostName: $('#hostName').val()\r\n"
"            };\r\n"
"\r\n"
"            UpdateGraph(null, parameters);\r\n"
"\r\n"
"            $.post(\"/parameters\", { parameters: JSON.stringify(parameters) })\r\n"
"                .done(function () { _unlock_screen(); });\r\n"
"        }\r\n"
"\r\n"
"        function SetManualPower(percent) {\r\n"
"            _lock_screen();\r\n"
"            $.post(\"/manual\", { percent: percent })\r\n"
"                .done(function () { _unlock_screen(); refresh(true); });\r\n"
"        }\r\n"
"\r\n"
"        $(function () {\r\n"
"            // initial refresh\r\n"
"            refresh(true);\r\n"
"\r\n"
"            // main refresh loop\r\n"
"            setInterval(refresh, 5000);\r\n"
"        })\r\n"
"    </script>\r\n"
"</body>\r\n"
"\r\n"
"</html\r\n"
;
