#include "Row.h"

void Row::serializeTo(uint8_t* dst) {
  memcpy(dst + ID_OFFSET, &id, ID_SIZE);
  memcpy(dst + USERNAME_OFFSET, username, USERNAME_SIZE);
  memcpy(dst + EMAIL_OFFSET, email, EMAIL_SIZE);
}
void Row::deserializeFrom(uint8_t* src) {
  memcpy(&id, src + ID_OFFSET, ID_SIZE);
  memcpy(&username, src + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&email, src + EMAIL_OFFSET, EMAIL_SIZE);
}
