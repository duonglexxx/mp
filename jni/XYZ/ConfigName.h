#pragma once

#define targetLib "liblogic.so"

struct sAim {
    struct sHelper {
        struct sSkills {
			bool Ling1;
            bool Basic;
            bool Spell;
			bool Spell2;
			bool Spell3;
			bool Flam;
            bool Skill1;
            bool Skill2;
            bool Skill3;
            bool Skill4;
			bool Yin;
			bool Gusion;
			bool Gusion2;
			bool Gusion3;
			bool Gusion4;
			bool Kimmy;
			bool Kimmy2;
			bool Paqito;
			bool Phasa;
			bool Phasa2;
			bool Oneb ;
			bool One2 ;
			bool One3 ;
            bool AutoBen;
			bool Twob ;
			bool Two1;
			bool Two3 ;
			bool Tree1 ;
			bool Tree2 ;
			bool Lunox;
			bool Harith;
			bool Yve1;
        };
        sSkills Skills{0};

        struct sPriority {
            int Target = 1;
			int Targe = 1;
			int Target2;
			int Post=1;
            bool AutoTakeSword;
        };
        sPriority Priority{0};
		
		struct sAutoRetribution {
            bool Buff;
            bool Turtle;
            bool Lord;
            bool Crab;
            bool Litho;
            bool Ling;
            bool Kimmy;
            bool Gusion;
            float Speed1 = 30;
            float Speed2 = 30;
            bool hasEnemyButton;
            int hasEnemyDistOnly;
            int iCalculateDamage;
        };
        sAutoRetribution AutoRetribution{0};
		
    };
    sHelper Helper{0};
    Vector3 Dir = Vector3::zero();
    Vector3 Pos = Vector3::One();
    Vector3 NearestEnemyPos = Vector3::zero();
    int NearestEnemyGuid = 0;
    bool RetriDistButton;
	float NearestEnemyDist = 9999;
};
sAim Aim{0};
//static float RangeFOV = 15.0f;
void (*orig_TryUseSkill)(...);

//void TryUseSkill(void*instance,int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack, bool bAlong, bool isInFirstDragRange) {
void TryUseSkill(void*instance,int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack, bool bAlong, bool isInFirstDragRange, bool bIgnoreQueue) {
	bool isDoneAim = false;
     if (instance != NULL) {
        float MaxDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        float MaxPercentHP = std::numeric_limits<float>::infinity();
        float MaxSwordDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP1 = std::numeric_limits<float>::infinity();
       float MaxDist1 = std::numeric_limits<float>::infinity();
        float MaxPercentHP1 = std::numeric_limits<float>::infinity();
        
		Vector3 EntityPos = Vector3::zero();
		Vector3 EntityPos1 = Vector3::zero();
        Vector3 SwordPos = Vector3::zero();

        void *BattleManager_Instance;
        Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
        if (BattleManager_Instance) {
            auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
            if (m_LocalPlayerShow) {
                auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
                if (selfPos != Vector3::zero()) {
                    monoList<void **> *m_ShowPlayers = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowPlayers);
                    if (m_ShowPlayers) {
                        for (int i = 0; i < m_ShowPlayers->getSize(); i++) {
                            auto Pawn = m_ShowPlayers->getItems()[i];
                            if (!Pawn) continue;
                            auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                            if (m_bSameCampType) continue;
                            auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                            if (m_bDeath) continue;
							auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);
                            float Distance = (int) Vector3::Distance(selfPos, _Position);
                            float Distanc = (int) Vector3::Distance(selfPos, _Position);
                           
							float CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                            float MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                            float PercentHP = CurHP * 100 / MaxHP;
							int skillId2 = 100 * HeroID + 20;
							int skillId1 = 100 * HeroID + 10;
						 
				
                      if (Distance < RangeFOV) {
                                if (Aim.Helper.Priority.Target == 0 && Distance < MaxDist) {
                                    EntityPos = _Position;
                                    MaxDist = Distance;
                                }
                                if (Aim.Helper.Priority.Target == 1 && CurHP < MaxEnemyHP) {
                                    EntityPos = _Position;
                                    MaxEnemyHP = CurHP;
                                }
                                if (Aim.Helper.Priority.Target == 2 && PercentHP < MaxPercentHP) {
                                    EntityPos = _Position;
                                    MaxPercentHP = PercentHP;
                                }
							}
						}
					}
				}
	monoList<void **> *_RunBullets;
                    Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "_RunBullets", &_RunBullets);
                     if (_RunBullets) {
                        for (int i = 0; i < _RunBullets->getSize(); i++) {
                            auto Pawn = _RunBullets->getItems()[i];
                            if (!Pawn) continue;
                            auto m_ID = *(int *) ((uintptr_t)Pawn + Bullet_m_Id);
                            if (m_ID != 8452) continue; 
                            auto transform = *(Transform **) ((uintptr_t)Pawn + Bullet_transform);
			
                            float Distance2 = (int) Vector3::Distance2(selfPos, transform->get_position());
                      if (Distance2 < 5) {
                            if (Distance2 < MaxSwordDist&&Aim.Helper.Priority.AutoTakeSword ) {
                                    SwordPos = transform->get_position();
                                    MaxSwordDist = Distance2;
                                }
                            }
                        }
                    }

                    if (SwordPos != Vector3::zero() && HeroID == 84) {
                        auto targetLockPos1 = Vector3::Normalized(SwordPos - selfPos);
                        if (skillId == 100 * HeroID + 20) {
                            isDoneAim = true;
							orig_TryUseSkill(instance, skillId, targetLockPos1, dirDefault, pos, bCommonAttack, bAlong, false);
                        }
                    }  
					
		  
		  else if (EntityPos != Vector3::zero()) {
		   auto LockPos = EntityPos;
		
          auto targetLockPos = Vector3::Normalized(EntityPos - selfPos);
		  
                     //Basic
                        if (Aim.Helper.Skills.Basic) {
                            if (skillId == 100 * HeroID + 00) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAttack, bAlong, false);
                            }
                        }
                        //Spell
                      
                        //Skill 1
                        if (Aim.Helper.Skills.Skill1) {
                            if (skillId == 100 * HeroID + 10) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);
                           }
                        }
					  //Skill 2
                        if (Aim.Helper.Skills.Skill2) {
                            if (skillId == 100 * HeroID + 20 || skillId == 2010520 /*Beatrix Skill2*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);
                           }
                        }
                        //Skill 3
                        if (Aim.Helper.Skills.Skill3) {
                            if (skillId == 100 * HeroID + 30 || skillId == 2010530 /*Beatrix Ulti*/) {
                                isDoneAim = true;
                             orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);                        
                          
							 }
                        }
                        //Skill 4
                        if (Aim.Helper.Skills.Skill4) {
                            if (skillId == 100 * HeroID + 40) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAttack, bAlong, false);                                  
                    }

                }
            }
        }
    }
	
}
    if (!isDoneAim) {
        orig_TryUseSkill(instance, skillId, dir, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange);
    }
}

