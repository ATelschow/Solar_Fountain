void taskcreation_setup()
{
#pragma region Taskcreation
xTaskCreatePinnedToCore(
                  Task1code,   /* Task function. */
                  "Task1",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &Task1,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */                  
//delay(500); 

//create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
xTaskCreatePinnedToCore(
                  Task2code,   /* Task function. */
                  "Task2",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &Task2,      /* Task handle to keep track of created task */
                  1);          /* pin task to core 1 */
//  delay(500); 
#pragma endregion Taskcreation
}