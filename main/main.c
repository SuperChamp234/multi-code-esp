#include <stdio.h>
#include <sra_board.h>
#include <freertos/FreeRTOS.h>

// Declare task handles
TaskHandle_t blink_task1_handle = NULL;
TaskHandle_t blink_task2_handle = NULL;

// Declare a constant tag for logging
static const char *TAG_TASK_HANDLER = "Task_Handler";

// Function to display a cool effect on the bar graph
void blink_task1(void *arg) {
    // Initialize the bar graph module
    ESP_ERROR_CHECK(enable_bar_graph());

    // Initialize a 8-bit integer to represent the bar graph
    uint8_t var = 0x01;

    // Continuously display the cool effect
    while (1) {
        // Reset the variable to 0x01 when it reaches 0
        if (var == 0x00) {
            var = 0x01;
        }

        // Set the bar graph based on the variable
        ESP_ERROR_CHECK(set_bar_graph(var));
        // Shift the variable to the left
        var = var << 1;
        // Wait for 1000ms
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Function to display the pattern 11001100 on the bar graph
void blink_task2(void *arg) {
    // Initialize the bar graph module
    ESP_ERROR_CHECK(enable_bar_graph());
    // Initialize a boolean array to represent the bar graph
    bool arr[8] = {true, true, false, false, true, true, false, false};
    
    // Continuously display the pattern
    while (1) {
        // Set the bar graph based on the boolean array
        ESP_ERROR_CHECK(set_bar_graph(bool_to_uint8(arr)));
        // Wait for 3000ms
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

// Function to control the bar graph display based on the state of the switches
void task_handler(void *args) {
    // Initialize the switch module
    enable_switches();
    // Log the start of the task
    ESP_LOGI(TAG_TASK_HANDLER, "Task Handler started");

    // Continuously monitor the state of the switches
    while (1) {
        // If switch 1 is pressed
        if (read_switch(SWITCH_1)) {
            // Log the switch press event
            ESP_LOGI(TAG_TASK_HANDLER, "Task 1 Starting, Halting Task 2");
            // Resume Task 1 and suspend Task 2
            vTaskResume(blink_task1_handle);
            vTaskSuspend(blink_task2_handle);
            // Wait for 1000ms
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        // If switch 2 is pressed
        else if (read_switch(SWITCH_2)) {
            // Log the switch press event
            ESP_LOGI(TAG_TASK_HANDLER, "Task 2 Starting, Halting Task 1");
            // Resume Task 2 and suspend Task 1
            vTaskResume(blink_task2_handle);
            vTaskSuspend(blink_task1_handle);
            // Wait for 1000ms
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// Main function
void app_main(void) {
    // Create the two tasks
    xTaskCreate(blink_task1, "blink_task1", 2048, NULL, 2, &blink_task1_handle);
    xTaskCreate(blink_task2, "blink_task2", 2048, NULL, 2, &blink_task2_handle);
    // Suspend the two tasks at the start
    vTaskSuspend(blink_task1_handle);
    vTaskSuspend(blink_task2_handle);
    // Create the task handler task
    xTaskCreate(task_handler, "task_handler", 2048, NULL, 2, NULL);
}