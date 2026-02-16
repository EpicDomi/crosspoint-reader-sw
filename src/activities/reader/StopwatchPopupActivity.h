#pragma once
#include <EpdFontFamily.h>
#include <HalDisplay.h>

#include <functional>

#include "../Activity.h"
#include "util/ButtonNavigator.h"

class StopwatchPopupActivity final : public Activity {
  unsigned long durationMs;
  int pagesRead;
  int estimatedRemainingSeconds;
  std::function<void()> onConfirm;

 public:
  explicit StopwatchPopupActivity(GfxRenderer& renderer, MappedInputManager& mappedInput, unsigned long durationMs,
                                  int pagesRead, int estimatedRemainingSeconds, std::function<void()> onConfirm)
      : Activity("StopwatchPopup", renderer, mappedInput),
        durationMs(durationMs),
        pagesRead(pagesRead),
        estimatedRemainingSeconds(estimatedRemainingSeconds),
        onConfirm(onConfirm) {}
  void onEnter() override;
  void loop() override;
};
