module.exports = [
  {
    "type": "section",
    "items": [
      { 
        "type": "heading", 
        "defaultValue": "Color up your Pebble!" 
      }, 
      { 
        "type": "text", 
        "defaultValue": "Choose your colors" 
      },
      {
        "type": "color",
        "messageKey": "COLOR_BACKGROUND",
        "defaultValue": "ff0000",
        "label": "Background Color",
        "sunlight": true
      },
      {
        "type": "color",
        "messageKey": "COLOR_PRIMARY",
        "defaultValue": "ffffff",
        "label": "Primary Color",
        "sunlight": true
      },
      {
        "type": "color",
        "messageKey": "COLOR_SECONDARY",
        "defaultValue": "000000",
        "label": "Secondary Color",
        "sunlight": true
      }
    ]
  },
  {
    "type": "section",
    "items": [
      { 
        "type": "heading", 
        "defaultValue": "Typography" 
      }, 
      { 
        "type": "text", 
        "defaultValue": "Customize your typeface." 
      },
      {
        "type": "select",
        "messageKey": "PRIMARY_FONT",
        "defaultValue": "0",
        "label": "Select the primary font.",
        "options": [
          { 
            "label": "Bitham 42 Bold", 
            "value": "0" 
          },
          { 
            "label": "Bitham 42 Light",
            "value": "1" 
          }
        ],
        "attributes": {
          "required": "required"
        }
      },
      {
        "type": "select",
        "messageKey": "SECONDARY_FONT",
        "defaultValue": "0",
        "label": "Select the secondary font.",
        "options": [
          { 
            "label": "Gothic 18", 
            "value": "5" 
          },
          { 
            "label": "Gothic 18 Bold",
            "value": "6" 
          }
        ],
        "attributes": {
          "required": "required"
        }
      }
    ]
  },
  {
    "type": "section",
    "items": [
      { 
        "type": "heading", 
        "defaultValue": "Widgets" 
      }, 
      { 
        "type": "text", 
        "defaultValue": "Customize your view when you shake it." 
      },
      {
        "type": "input",
        "messageKey": "TEXT_LABEL",
        "defaultValue": "",
        "label": "Label your own Timezone",
        "attributes": {
          "placeholder": "UTC",
          "limit": 5,
          "required": "required",
          "type": "text"
        }
      },
      {
        "type": "select",
        "messageKey": "STRING_UTC_OFFSET",
        "defaultValue": "UTC",
        "label": "Select the UTC offset of your Timezone",
        "options": [
          { 
            "label": "", 
            "value": "" 
          },
          { 
            "label": "UTC-12",
            "value": "-720" 
          },
          { 
            "label": "UTC-11",
            "value": "-660" 
          },
          { 
            "label": "UTC-10",
            "value": "-600" 
          },
          { 
            "label": "UTC-09:30",
            "value": "-570" 
          },
          { 
            "label": "UTC-09",
            "value": "-540" 
          },
          { 
            "label": "UTC-08",
            "value": "-480" 
          },
          { 
            "label": "UTC-07",
            "value": "-420" 
          },
          { 
            "label": "UTC-06",
            "value": "-360" 
          },
          { 
            "label": "UTC-05",
            "value": "-300" 
          },
          { 
            "label": "UTC-04",
            "value": "-240" 
          },
          { 
            "label": "UTC-03:30",
            "value": "-210" 
          },
          { 
            "label": "UTC-03",
            "value": "-180" 
          },
          { 
            "label": "UTC-02",
            "value": "-120" 
          },
          { 
            "label": "UTC-01",
            "value": "-60" 
          },
          { 
            "label": "UTC",
            "value": "0" 
          },
          { 
            "label": "UTC+01",
            "value": "60" 
          },
          { 
            "label": "UTC+02",
            "value": "120" 
          },
          { 
            "label": "UTC+03",
            "value": "180" 
          },
          { 
            "label": "UTC+04:30",
            "value": "270" 
          },
          { 
            "label": "UTC+04",
            "value": "240" 
          },
          { 
            "label": "UTC+05:30",
            "value": "330" 
          },
          { 
            "label": "UTC+05:45",
            "value": "345" 
          },
          { 
            "label": "UTC+05",
            "value": "300" 
          },
          { 
            "label": "UTC+06",
            "value": "360" 
          },
          { 
            "label": "UTC+06:30",
            "value": "390" 
          },
          { 
            "label": "UTC+07",
            "value": "420" 
          },
          { 
            "label": "UTC+08",
            "value": "480" 
          },
          { 
            "label": "UTC+08:30",
            "value": "510" 
          },
          { 
            "label": "UTC+08:45",
            "value": "525" 
          },
          { 
            "label": "UTC+09",
            "value": "540" 
          },
          { 
            "label": "UTC+09:30",
            "value": "570" 
          },
          { 
            "label": "UTC+10",
            "value": "600" 
          },
          { 
            "label": "UTC+10:30",
            "value": "630" 
          },
          { 
            "label": "UTC+11",
            "value": "660" 
          },
          { 
            "label": "UTC+12",
            "value": "720" 
          },
          { 
            "label": "UTC+12:45",
            "value": "765" 
          },
          { 
            "label": "UTC+13",
            "value": "780" 
          },
          { 
            "label": "UTC+14",
            "value": "840" 
          }
        ],
        "attributes": {
          "required": "required"
        }
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save"
  }
];