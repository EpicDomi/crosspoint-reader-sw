#include "StopwatchPopupActivity.h"

#include <GfxRenderer.h>
#include <I18n.h>

#include <cstdio>

#include "fontIds.h"

static void formatTime(unsigned long totalSeconds, char* buffer, size_t size) {
  unsigned long hours = totalSeconds / 3600;
  unsigned long minutes = (totalSeconds % 3600) / 60;
  unsigned long seconds = totalSeconds % 60;
  snprintf(buffer, size, "%lu:%02lu:%02lu", hours, minutes, seconds);
}

void StopwatchPopupActivity::onEnter() {
  Activity::onEnter();

  int screenW = renderer.getScreenWidth();
  int screenH = renderer.getScreenHeight();

  int boxW = 400;
  int boxH = 250;
  int boxX = (screenW - boxW) / 2;
  int boxY = (screenH - boxH) / 2;

  // Clear and Border
  renderer.fillRect(boxX, boxY, boxW, boxH, false);
  renderer.drawRect(boxX, boxY, boxW, boxH, true);

  unsigned long totalSeconds = durationMs / 1000;
  char timeStr[32];
  formatTime(totalSeconds, timeStr, sizeof(timeStr));

  // --- Line 1: In [Time] ---
  const char* inStr = tr(STR_SW_IN);
  int w1 = renderer.getTextWidth(UI_12_FONT_ID, inStr, EpdFontFamily::REGULAR);
  int w2 = renderer.getSpaceWidth(UI_12_FONT_ID);
  int w3 = renderer.getTextWidth(UI_12_FONT_ID, timeStr, EpdFontFamily::BOLD);
  int totalW = w1 + w2 + w3;

  int x = (screenW - totalW) / 2;
  int y = boxY + 40;

  renderer.drawText(UI_12_FONT_ID, x, y, inStr, true, EpdFontFamily::REGULAR);
  x += w1 + w2;
  renderer.drawText(UI_12_FONT_ID, x, y, timeStr, true, EpdFontFamily::BOLD);

  y += renderer.getLineHeight(UI_12_FONT_ID) + 2;

  // --- Line 2: you have read [X] page(s) ---
  char pageCountStr[64];
  snprintf(pageCountStr, sizeof(pageCountStr), "%d %s", pagesRead,
           (pagesRead == 1 ? tr(STR_SW_PAGE) : tr(STR_SW_PAGES)));

  const char* readStr = tr(STR_SW_READ);
  w1 = renderer.getTextWidth(UI_12_FONT_ID, readStr, EpdFontFamily::REGULAR);
  w2 = renderer.getSpaceWidth(UI_12_FONT_ID);
  w3 = renderer.getTextWidth(UI_12_FONT_ID, pageCountStr, EpdFontFamily::BOLD);
  totalW = w1 + w2 + w3;

  x = (screenW - totalW) / 2;
  renderer.drawText(UI_12_FONT_ID, x, y, readStr, true, EpdFontFamily::REGULAR);
  x += w1 + w2;
  renderer.drawText(UI_12_FONT_ID, x, y, pageCountStr, true, EpdFontFamily::BOLD);

  y += 40;

  // --- Line 3: Estimation ---
  if (estimatedRemainingSeconds >= 0) {
    char estTimeStr[32];
    formatTime(estimatedRemainingSeconds, estTimeStr, sizeof(estTimeStr));

    renderer.drawCenteredText(UI_10_FONT_ID, y, tr(STR_SW_RATE_PREFIX), true, EpdFontFamily::REGULAR);
    y += renderer.getLineHeight(UI_10_FONT_ID) + 2;

    const char* finishStr = tr(STR_SW_FINISH_IN);
    w1 = renderer.getTextWidth(UI_10_FONT_ID, finishStr, EpdFontFamily::REGULAR);
    w2 = renderer.getSpaceWidth(UI_10_FONT_ID);
    w3 = renderer.getTextWidth(UI_10_FONT_ID, estTimeStr, EpdFontFamily::BOLD);
    totalW = w1 + w2 + w3;

    x = (screenW - totalW) / 2;
    renderer.drawText(UI_10_FONT_ID, x, y, finishStr, true, EpdFontFamily::REGULAR);
    x += w1 + w2;
    renderer.drawText(UI_10_FONT_ID, x, y, estTimeStr, true, EpdFontFamily::BOLD);

    y += 40;
  } else {
    y += 20;
  }

  renderer.drawCenteredText(UI_10_FONT_ID, y, tr(STR_SW_CLOSE_HINT), true, EpdFontFamily::ITALIC);
  renderer.displayBuffer(HalDisplay::FAST_REFRESH);
}

void StopwatchPopupActivity::loop() {
  if (mappedInput.wasReleased(MappedInputManager::Button::Confirm)) {
    if (onConfirm) onConfirm();
  }
}
