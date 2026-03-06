#pragma once
#include <EpdFontFamily.h>
#include <HalDisplay.h>

#include "../Activity.h"

class StopwatchPopupActivity final : public Activity {
  unsigned long durationMs;
  int pagesRead;
  int estimatedRemainingSeconds;

 public:
  explicit StopwatchPopupActivity(GfxRenderer& renderer, MappedInputManager& mappedInput, unsigned long durationMs,
                                  int pagesRead, int estimatedRemainingSeconds)
      : Activity("StopwatchPopup", renderer, mappedInput),
        durationMs(durationMs),
        pagesRead(pagesRead),
        estimatedRemainingSeconds(estimatedRemainingSeconds) {}
  void onEnter() override;
  void render(RenderLock&&) override;
  void loop() override;
};
