target_sources(app
        PRIVATE
        pd_controller.c
        adc_controller.c
        adc_probe.c
        display.c )

target_include_directories(app PRIVATE .)