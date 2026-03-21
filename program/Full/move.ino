void moveX(float x) {
  CurrentX += x;

  long Iterations = x * IterPerMilliX;
  if (Iterations < 0) {
    Iterations = abs(Iterations);
    digitalWrite(DIR_PIN_X, HIGH);
  } else {
    digitalWrite(DIR_PIN_X, LOW);
  }
  while (Iterations > 0) {
    digitalWrite(STEP_PIN_X, HIGH);
    delayMicroseconds(StepDelayX);
    digitalWrite(STEP_PIN_X, LOW);
    delayMicroseconds(StepDelayX);
    Iterations -= 1;
  }
}

void moveY(float y) {
  CurrentY += y;

  long Iterations = y * IterPerMilliY;
  if (Iterations < 0) {
    Iterations = abs(Iterations);
    digitalWrite(DIR_PIN_Y, LOW);
  } else {
    digitalWrite(DIR_PIN_Y, HIGH);
  }
  while (Iterations > 0) {
    digitalWrite(STEP_PIN_Y, HIGH);
    delayMicroseconds(StepDelayY);
    digitalWrite(STEP_PIN_Y, LOW);
    delayMicroseconds(StepDelayY);
    Iterations -= 1;
  }
}

void moveXY(float x, float y) {
  if (x == 0) {
    moveY(y);
  } else if (y == 0) {
    moveX(x);
  } else {
    CurrentX += x;
    CurrentY += y;
    IterationsX = x * IterPerMilliX;
    IterationsY = y * IterPerMilliY;

    if (IterationsX < 0) {
      IterationsX = abs(IterationsX);
      digitalWrite(DIR_PIN_X, HIGH);
    } else {
      digitalWrite(DIR_PIN_X, LOW);
    }

    if (IterationsY < 0) {
      IterationsY = abs(IterationsY);
      digitalWrite(DIR_PIN_Y, LOW);
    } else {
      digitalWrite(DIR_PIN_Y, HIGH);
    }

    float TimeX = 2 * StepDelayX * IterationsX;
    float TimeY = 2 * StepDelayY * IterationsY;
    float TimeXY = max(TimeX, TimeY);
    float StepDelayXUmn = StepDelayX * TimeXY / TimeX;
    float StepDelayYUmn = StepDelayY * TimeXY / TimeY;

    StepStateX = HIGH;
    StepStateY = HIGH;
    unsigned long LastChangeStepX = micros();
    unsigned long LastChangeStepY = micros();

    Serial.println("X:");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(IterationsX * StepDelayXUmn);
    Serial.println(IterationsX / IterPerMilliX);
    Serial.println(StepDelayXUmn);
    Serial.println(IterationsX);

    Serial.println("Y:");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(IterationsY * StepDelayYUmn);
    Serial.println(IterationsY / IterPerMilliY);
    Serial.println(StepDelayYUmn);
    Serial.println(IterationsY);


    uint32_t myTime = micros();
    while (IterationsX > 0 || IterationsY > 0) {
      if (micros() - LastChangeStepY >= StepDelayYUmn) {
        changeStepY();
        LastChangeStepY = micros();
      }
      if (micros() - LastChangeStepX >= StepDelayXUmn) {
        changeStepX();
        LastChangeStepX = micros();
      }
      
    }
    // delay(10);
    Serial.println(micros() - LastChangeStepX);
    Serial.println(micros() - LastChangeStepY);

    delayMicroseconds(min(StepDelayXUmn, StepDelayYUmn));
    Serial.println("Itog: ");
    Serial.print("IterationsX: ");
    Serial.println(IterationsX);
    Serial.print("IterationsY: ");
    Serial.println(IterationsY);

    Serial.println(" ");
  }
}

void moveToXY(float NeededX, float NeededY) {
  float deltaX = NeededX - CurrentX;
  float deltaY = NeededY - CurrentY;
  moveXY(deltaX, deltaY);
}

void moveXY_Bresenham(float x, float y) {
    // 1. Рассчитываем целевое количество шагов (как и раньше, но округляем до long)
    long targetStepsX = (long)(x * IterPerMilliX + (x > 0 ? 0.5 : -0.5));
    long targetStepsY = (long)(y * IterPerMilliY + (y > 0 ? 0.5 : -0.5));

    // Если перемещение нулевое, выходим
    if (targetStepsX == 0 && targetStepsY == 0) return;

    // 2. Определяем направление для каждой оси
    if (targetStepsX < 0) {
        targetStepsX = -targetStepsX;
        digitalWrite(DIR_PIN_X, HIGH); // Направление для X (подбери под свою механику)
    } else {
        digitalWrite(DIR_PIN_X, LOW);
    }

    if (targetStepsY < 0) {
        targetStepsY = -targetStepsY;
        digitalWrite(DIR_PIN_Y, LOW);  // Направление для Y (подбери под свою механику)
    } else {
        digitalWrite(DIR_PIN_Y, HIGH);
    }

    // 3. Определяем ведущую ось (ту, по которой шагов больше)
    // и настраиваем параметры алгоритма Брезенхема
    long totalSteps;          // Общее количество шагов (тактов алгоритма)
    long stepsMajor;          // Шаги по ведущей оси (совпадает с totalSteps)
    long stepsMinor;          // Шаги по ведомой оси
    bool majorIsX;            // Флаг: true - ведущая ось X, false - ведущая ось Y

    if (targetStepsX >= targetStepsY) {
        // Ведущая ось - X
        totalSteps = targetStepsX;
        stepsMajor = targetStepsX;
        stepsMinor = targetStepsY;
        majorIsX = true;
    } else {
        // Ведущая ось - Y
        totalSteps = targetStepsY;
        stepsMajor = targetStepsY;
        stepsMinor = targetStepsX;
        majorIsX = false;
    }

    // 4. Инициализация аккумулятора ошибки для алгоритма Брезенхема
    // Классическая инициализация: accumulator = 2 * stepsMinor - totalSteps
    // Но для более равномерного распределения часто используют смещение: accumulator = 2 * stepsMinor - totalSteps [citation:9]
    // Чтобы избежать крена в начале, можно инициализировать accumulator = 2 * stepsMinor - totalSteps.
    long accumulator = 2 * stepsMinor - totalSteps;

    // 5. Счётчики выполненных шагов
    long stepsDoneMajor = 0;
    long stepsDoneMinor = 0;

    // 6. Обновляем глобальные координаты (ДО начала движения, как у тебя)
    // Но лучше обновлять их после успешного завершения, чтобы избежать рассинхрона при ошибках.
    // Я оставлю как у тебя, но на будущее рекомендую перенести после цикла.
    CurrentX += x;
    CurrentY += y;

    // 7. Основной цикл алгоритма (блокирующий)
    // Цикл выполняется, пока не сделаны все шаги по ведущей оси
    while (stepsDoneMajor < totalSteps) {
        // --- Шаг по ведущей оси (делается на каждой итерации) ---
        if (majorIsX) {
            doStepX(); // Твоя функция, выдающая импульс на STEP_PIN_X
        } else {
            doStepY(); // Твоя функция, выдающая импульс на STEP_PIN_Y
        }
        stepsDoneMajor++;

        // --- Проверка, нужно ли сделать шаг по ведомой оси ---
        if (accumulator > 0) {
            // Делаем шаг по ведомой оси
            if (majorIsX) {
                doStepY();
            } else {
                doStepX();
            }
            stepsDoneMinor++;
            // Корректируем аккумулятор: вычитаем 2 * totalSteps [citation:9]
            accumulator -= 2 * totalSteps;
        }

        // --- Обновляем аккумулятор для следующей итерации ---
        accumulator += 2 * stepsMinor;

        // Здесь можно добавить микро-задержку, чтобы контролировать скорость.
        // Но в реальных проектах скорость регулируется частотой тактов этого цикла (например, по прерыванию таймера).
        // Для блокирующего варианта можно использовать delayMicroseconds(StepDelayX),
        // но тогда скорость будет ограничена самой медленной осью.
        // Лучше вынести генерацию импульсов в прерывание по таймеру, а в этом цикле только принимать решения.
        // Пока оставим минимальную задержку, чтобы не спамить шаги.
        delayMicroseconds(50); // ОЧЕНЬ грубая задержка, требует доработки!
    }

    // Пост-проверка (для отладки)
    // if (stepsDoneMinor != stepsMinor) {
    //     Serial.println("Ошибка алгоритма Брезенхема!");
    // }
}

// Вспомогательные функции для импульса (добавь их, если ещё нет)
void doStepX() {
    digitalWrite(STEP_PIN_X, HIGH);
    delayMicroseconds(5); // Длительность импульса под твой драйвер
    digitalWrite(STEP_PIN_X, LOW);
}

void doStepY() {
    digitalWrite(STEP_PIN_Y, HIGH);
    delayMicroseconds(5);
    digitalWrite(STEP_PIN_Y, LOW);
}