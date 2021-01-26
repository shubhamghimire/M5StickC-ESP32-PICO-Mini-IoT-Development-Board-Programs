volatile int g_ev_cnt = 0;
volatile apb_change_ev_t b_ev_type;
volatile apb_change_ev_t a_ev_type;
volatile uint32_t b_old_apb;
volatile uint32_t b_new_apb;
volatile uint32_t a_old_apb;
volatile uint32_t a_new_apb;

static void _on_apb_change(void * arg, apb_change_ev_t ev_type, uint32_t old_apb, uint32_t new_apb){
  g_ev_cnt++;
  if (ev_type == APB_BEFORE_CHANGE){
    b_ev_type = ev_type;
    b_old_apb = old_apb;
    b_new_apb = new_apb;
  }
  else if (APB_AFTER_CHANGE){
    a_ev_type = ev_type;
    a_old_apb = old_apb;
    a_new_apb = new_apb;
  }
}

uint32_t iarg = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.printf("getXtalFrequencyMhz() : %d\n", getXtalFrequencyMhz());
  Serial.printf("getCpuFrequencyMhz() : %d\n", getCpuFrequencyMhz());
  Serial.printf("getApbFrequency() : %d\n", getApbFrequency());

  Serial.printf("\n");

  Serial.printf("addApbChangeCallback() : %d\n", addApbChangeCallback((void*)iarg, _on_apb_change));
  Serial.printf("g_ev_cnt : %d, b_ev_type : %d, b_old_apb : %d, b_new_apb : %d\n", g_ev_cnt, b_ev_type, b_old_apb);
  Serial.printf("g_ev_cnt : %d, a_ev_type : %d, a_old_apb : %d, a_new_apb : %d\n", g_ev_cnt, a_ev_type, a_old_apb);

  Serial.printf("\n");

  for (int i = 0; i <= 500 ; i++){
    int ret = setCpuFrequencyMhz(i);
    if(ret){
      Serial.printf("setCpuFrequencyMhz(%d) : %d\n", i, ret);
      Serial.printf("setCpuFrequencyMhz() : %d\n", getCpuFrequencyMhz());
      Serial.printf("getApbFrequency() : %d\n", getApbFrequency());
      Serial.printf("getXtalFrequencyMhz() : %d\n", getXtalFrequencyMhz());
      Serial.printf("g_cv_cnt : %d, b_ev_type : %d, b_old_apb : %d, b_new_apb : %d\n", g_ev_cnt, b_ev_type, b_old_apb, b_new_apb);
      Serial.printf("g_cv_cnt : %d, a_ev_type : %d, a_old_apb : %d, a_new_apb : %d\n", g_ev_cnt, a_ev_type, a_old_apb, a_new_apb);
      Serial.printf("\n");
    }
  }
  Serial.printf("removeApbChangeCallback() : %d\n", removeApbChangeCallback((void*)iarg, _on_apb_change));
}

void loop() {
  // put your main code here, to run repeatedly:

}
