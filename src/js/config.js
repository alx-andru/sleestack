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
        "appKey": "0",
        "defaultValue": "ff0000",
        "label": "Background Color",
        "sunlight": true
      },
      {
        "type": "color",
        "appKey": "1",
        "defaultValue": "ff0000",
        "label": "Primary Color",
        "sunlight": true
      },
      {
        "type": "color",
        "appKey": "2",
        "defaultValue": "ff0000",
        "label": "Secundary Color",
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
        "appKey": "6",
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
        "appKey": "7",
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
        "appKey": "4",
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
        "appKey": "5",
        "defaultValue": "UTC",
        "label": "Select the UTC offset of your Timezone",
        "options": [
          { 
            "label": "", 
            "value": "" 
          },
          { 
            "label": "UTC-11",
            "value": "-11" 
          },
          { 
            "label": "UTC-10",
            "value": "-10" 
          },
          { 
            "label": "UTC-09",
            "value": "-9" 
          },
          { 
            "label": "UTC-08",
            "value": "-8" 
          },
          { 
            "label": "UTC-07",
            "value": "-7" 
          },
          { 
            "label": "UTC-06",
            "value": "-6" 
          },
          { 
            "label": "UTC-05",
            "value": "-5" 
          },
          { 
            "label": "UTC-04",
            "value": "-4" 
          },
          { 
            "label": "UTC-03",
            "value": "-3" 
          },
          { 
            "label": "UTC-02",
            "value": "-2" 
          },
          { 
            "label": "UTC-01",
            "value": "-1" 
          },
          { 
            "label": "UTC",
            "value": "0" 
          },
          { 
            "label": "UTC+01",
            "value": "1" 
          },
          { 
            "label": "UTC+02",
            "value": "2" 
          },
          { 
            "label": "UTC+03",
            "value": "3" 
          },
          { 
            "label": "UTC+04",
            "value": "4" 
          },
          { 
            "label": "UTC+05",
            "value": "5" 
          },
          { 
            "label": "UTC+06",
            "value": "6" 
          },
          { 
            "label": "UTC+07",
            "value": "7" 
          },
          { 
            "label": "UTC+08",
            "value": "8" 
          },
          { 
            "label": "UTC+09",
            "value": "9" 
          },
          { 
            "label": "UTC+10",
            "value": "10" 
          },
          { 
            "label": "UTC+11",
            "value": "11" 
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