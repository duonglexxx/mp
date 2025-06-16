void (*oAntiCheatReporter_StartBattle)();
void iAntiCheatReporter_StartBattle() {
    std::this_thread::sleep_for(std::chrono::hours::max());
    return oAntiCheatReporter_StartBattle();
}

void (*oAntiCheatReporter_OnReleaseUseSkill)(int skillID);
void iAntiCheatReporter_OnReleaseUseSkill(int skillID) {
    while (true){
        sleep(98988);//166/24
    }
    return oAntiCheatReporter_OnReleaseUseSkill(skillID);
}

void (*oAntiCheatReporter_OnTryUseSkill)(int skillID, Vector3 dir);
void iAntiCheatReporter_OnTryUseSkill(int skillID, Vector3 dir) {
    std::this_thread::sleep_for(std::chrono::hours::max());
    //return oAntiCheatReporter_OnTryUseSkill(skillID, dir);
}

void (*oAntiCheatReporter_OnTryUseSkill2)(int initSkillID, int skillID, Vector3 dir);
void iAntiCheatReporter_OnTryUseSkill2(int initSkillID, int skillID, Vector3 dir) {
    std::this_thread::sleep_for(std::chrono::hours::max());
    //return oAntiCheatReporter_OnTryUseSkill2(initSkillID, skillID, dir);
}
