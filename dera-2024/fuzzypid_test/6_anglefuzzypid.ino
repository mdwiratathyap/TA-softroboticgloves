float anglefuzzy_error;
float anglefuzzy_lasterror;
float anglefuzzy_derror;

// Fuzzy
Fuzzy *angle_fuzzypid = new Fuzzy();

// FuzzyInput
FuzzySet *nEangle = new FuzzySet(-60, -30, -30, 15);
FuzzySet *zEangle = new FuzzySet(-15, 0, 0, 15);
FuzzySet *pEangle = new FuzzySet(-15, 30, 30, 60);

// FuzzyInput
FuzzySet *ndEangle = new FuzzySet(-1.5, -0.75, -0.75, 0.375);
FuzzySet *zdEangle = new FuzzySet(-0.375, 0, 0, 0.375);
FuzzySet *pdEangle = new FuzzySet(-0.375, 0.75, 0.75, 1.5);

// FuzzyOutput
FuzzySet *nKpangle = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKpangle = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKpangle = new FuzzySet(-0.5, 0.75, 0.75, 1);

// FuzzyOutput
FuzzySet *nKiangle = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKiangle = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKiangle = new FuzzySet(-0.5, 0.75, 0.75, 1);

// FuzzyOutput
FuzzySet *nKdangle = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKdangle = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKdangle = new FuzzySet(-0.5, 0.75, 0.75, 1);

void angle_fuzzypidSetup()
{
  // FuzzyInput
  FuzzyInput *errorangle = new FuzzyInput(1);
  errorangle->addFuzzySet(nEangle);
  errorangle->addFuzzySet(zEangle);
  errorangle->addFuzzySet(pEangle);
  angle_fuzzypid->addFuzzyInput(errorangle);

  // FuzzyInput
  FuzzyInput *derrorangle = new FuzzyInput(2);
  derrorangle->addFuzzySet(ndEangle);
  derrorangle->addFuzzySet(zdEangle);
  derrorangle->addFuzzySet(pdEangle);
  angle_fuzzypid->addFuzzyInput(derrorangle);

  // FuzzyOutput
  FuzzyOutput *Kpfangle = new FuzzyOutput(1);
  Kpfangle->addFuzzySet(nKpangle);
  Kpfangle->addFuzzySet(zKpangle);
  Kpfangle->addFuzzySet(pKpangle);
  angle_fuzzypid->addFuzzyOutput(Kpfangle);

  // FuzzyOutput
  FuzzyOutput *Kifangle = new FuzzyOutput(2);
  Kifangle->addFuzzySet(nKiangle);
  Kifangle->addFuzzySet(zKiangle);
  Kifangle->addFuzzySet(pKiangle);
  angle_fuzzypid->addFuzzyOutput(Kifangle);

  // FuzzyOutput
  FuzzyOutput *Kdfangle = new FuzzyOutput(3);
  Kdfangle->addFuzzySet(nKdangle);
  Kdfangle->addFuzzySet(zKdangle);
  Kdfangle->addFuzzySet(pKdangle);
  angle_fuzzypid->addFuzzyOutput(Kdfangle);

  // Building FuzzyRule 1
  FuzzyRuleAntecedent *ifENandDEN = new FuzzyRuleAntecedent();
  ifENandDEN->joinWithAND(nEangle, ndEangle);
  FuzzyRuleConsequent *thenNKPandNKIandZKD = new FuzzyRuleConsequent();
  thenNKPandNKIandZKD->addOutput(nKpangle);
  thenNKPandNKIandZKD->addOutput(nKiangle);
  thenNKPandNKIandZKD->addOutput(zKdangle);
  FuzzyRule *fuzzypidRule1 = new FuzzyRule(1, ifENandDEN, thenNKPandNKIandZKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule1);

  // Building FuzzyRule 2
  FuzzyRuleAntecedent *ifENandDEZ = new FuzzyRuleAntecedent();
  ifENandDEZ->joinWithAND(nEangle, zdEangle);
  FuzzyRuleConsequent *thenNKPandNKIandPKD = new FuzzyRuleConsequent();
  thenNKPandNKIandPKD->addOutput(nKpangle);
  thenNKPandNKIandPKD->addOutput(nKiangle);
  thenNKPandNKIandPKD->addOutput(pKdangle);
  FuzzyRule *fuzzypidRule2 = new FuzzyRule(2, ifENandDEZ, thenNKPandNKIandPKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule2);

  // Building FuzzyRule 3
  FuzzyRuleAntecedent *ifENandDEP = new FuzzyRuleAntecedent();
  ifENandDEP->joinWithAND(nEangle, pdEangle);
  FuzzyRuleConsequent *thenZKPandZKIandPKD = new FuzzyRuleConsequent();
  thenZKPandZKIandPKD->addOutput(zKpangle);
  thenZKPandZKIandPKD->addOutput(zKiangle);
  thenZKPandZKIandPKD->addOutput(pKdangle);
  FuzzyRule *fuzzypidRule3 = new FuzzyRule(3, ifENandDEP, thenZKPandZKIandPKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule3);

  // Building FuzzyRule 4
  FuzzyRuleAntecedent *ifEZandDEN = new FuzzyRuleAntecedent();
  ifEZandDEN->joinWithAND(zEangle, ndEangle);
  FuzzyRuleConsequent *thenZKPandNKIandPKD = new FuzzyRuleConsequent();
  thenZKPandNKIandPKD->addOutput(zKpangle);
  thenZKPandNKIandPKD->addOutput(nKiangle);
  thenZKPandNKIandPKD->addOutput(pKdangle);
  FuzzyRule *fuzzypidRule4 = new FuzzyRule(4, ifEZandDEN, thenZKPandNKIandPKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule4);

  // Building FuzzyRule 5
  FuzzyRuleAntecedent *ifEZandDEZ = new FuzzyRuleAntecedent();
  ifEZandDEZ->joinWithAND(zEangle, zdEangle);
  FuzzyRuleConsequent *thenZKPandZKIandZKD = new FuzzyRuleConsequent();
  thenZKPandZKIandZKD->addOutput(zKpangle);
  thenZKPandZKIandZKD->addOutput(zKiangle);
  thenZKPandZKIandZKD->addOutput(zKdangle);
  FuzzyRule *fuzzypidRule5 = new FuzzyRule(5, ifEZandDEZ, thenZKPandZKIandZKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule5);

  // Building FuzzyRule 6
  FuzzyRuleAntecedent *ifEZandDEP = new FuzzyRuleAntecedent();
  ifEZandDEP->joinWithAND(zEangle, pdEangle);
  FuzzyRuleConsequent *thenZKPandPKIandNKD = new FuzzyRuleConsequent();
  thenZKPandPKIandNKD->addOutput(zKpangle);
  thenZKPandPKIandNKD->addOutput(pKiangle);
  thenZKPandPKIandNKD->addOutput(nKdangle);
  FuzzyRule *fuzzypidRule6 = new FuzzyRule(6, ifEZandDEP, thenZKPandPKIandNKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule6);

  // Building FuzzyRule 7
  FuzzyRuleAntecedent *ifEPandDEN = new FuzzyRuleAntecedent();
  ifEPandDEN->joinWithAND(pEangle, ndEangle);
  FuzzyRuleConsequent *thenZKPandZKIanNPKD = new FuzzyRuleConsequent();
  thenZKPandZKIanNPKD->addOutput(zKpangle);
  thenZKPandZKIanNPKD->addOutput(zKiangle);
  thenZKPandZKIanNPKD->addOutput(nKdangle);
  FuzzyRule *fuzzypidRule7 = new FuzzyRule(7, ifEPandDEN, thenZKPandZKIanNPKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule7);

  // Building FuzzyRule 8
  FuzzyRuleAntecedent *ifEPandDEZ = new FuzzyRuleAntecedent();
  ifEPandDEZ->joinWithAND(pEangle, zdEangle);
  FuzzyRuleConsequent *thenPKPandPKIandNKD = new FuzzyRuleConsequent();
  thenPKPandPKIandNKD->addOutput(pKpangle);
  thenPKPandPKIandNKD->addOutput(pKiangle);
  thenPKPandPKIandNKD->addOutput(nKdangle);
  FuzzyRule *fuzzypidRule8 = new FuzzyRule(8, ifEPandDEZ, thenPKPandPKIandNKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule8);

  // Building FuzzyRule 9
  FuzzyRuleAntecedent *ifEPandDEP = new FuzzyRuleAntecedent();
  ifEPandDEP->joinWithAND(pEangle, pdEangle);
  FuzzyRuleConsequent *thenPKPandPKIandZKD = new FuzzyRuleConsequent();
  thenPKPandPKIandZKD->addOutput(pKpangle);
  thenPKPandPKIandZKD->addOutput(pKiangle);
  thenPKPandPKIandZKD->addOutput(zKdangle);
  FuzzyRule *fuzzypidRule9 = new FuzzyRule(9, ifEPandDEP, thenPKPandPKIandZKD);
  angle_fuzzypid->addFuzzyRule(fuzzypidRule9);
}
