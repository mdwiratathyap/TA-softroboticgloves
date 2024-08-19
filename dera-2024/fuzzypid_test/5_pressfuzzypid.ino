float pressfuzzy_error;
float pressfuzzy_lasterror;
float pressfuzzy_derror;

// Fuzzy
Fuzzy *press_fuzzypid = new Fuzzy();

// FuzzyInput
FuzzySet *nE = new FuzzySet(-100, -50, -50, 25);
FuzzySet *zE = new FuzzySet(-25, 0, 0, 25);
FuzzySet *pE = new FuzzySet(-25, 50, 50, 100);

// FuzzyInput
FuzzySet *ndE = new FuzzySet(-2.5, -1.25, -1.25, 0.625);
FuzzySet *zdE = new FuzzySet(-0.625, 0, 0, 0.625);
FuzzySet *pdE = new FuzzySet(-0.625, 1, 1, 2.5);

// FuzzyOutput
FuzzySet *nKp = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKp = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKp = new FuzzySet(-0.5, 0.75, 0.75, 1);

// FuzzyOutput
FuzzySet *nKi = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKi = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKi = new FuzzySet(-0.5, 0.75, 0.75, 1);

// FuzzyOutput
FuzzySet *nKd = new FuzzySet(-1, -0.75, -0.75, 0.5);
FuzzySet *zKd = new FuzzySet(-0.5, 0, 0, 0.5);
FuzzySet *pKd = new FuzzySet(-0.5, 0.75, 0.75, 1);

void press_fuzzypidSetup()
{
  // FuzzyInput
  FuzzyInput *error = new FuzzyInput(1);
  error->addFuzzySet(nE);
  error->addFuzzySet(zE);
  error->addFuzzySet(pE);
  press_fuzzypid->addFuzzyInput(error);

  // FuzzyInput
  FuzzyInput *derror = new FuzzyInput(2);
  derror->addFuzzySet(ndE);
  derror->addFuzzySet(zdE);
  derror->addFuzzySet(pdE);
  press_fuzzypid->addFuzzyInput(derror);

  // FuzzyOutput
  FuzzyOutput *Kpf = new FuzzyOutput(1);
  Kpf->addFuzzySet(nKp);
  Kpf->addFuzzySet(zKp);
  Kpf->addFuzzySet(pKp);
  press_fuzzypid->addFuzzyOutput(Kpf);

  // FuzzyOutput
  FuzzyOutput *Kif = new FuzzyOutput(2);
  Kif->addFuzzySet(nKi);
  Kif->addFuzzySet(zKi);
  Kif->addFuzzySet(pKi);
  press_fuzzypid->addFuzzyOutput(Kif);

  // FuzzyOutput
  FuzzyOutput *Kdf = new FuzzyOutput(3);
  Kdf->addFuzzySet(nKd);
  Kdf->addFuzzySet(zKd);
  Kdf->addFuzzySet(pKd);
  press_fuzzypid->addFuzzyOutput(Kdf);

  // Building FuzzyRule 1
  FuzzyRuleAntecedent *ifENandDEN = new FuzzyRuleAntecedent();
  ifENandDEN->joinWithAND(nE, ndE);
  FuzzyRuleConsequent *thenNKPandNKIandZKD = new FuzzyRuleConsequent();
  thenNKPandNKIandZKD->addOutput(nKp);
  thenNKPandNKIandZKD->addOutput(nKi);
  thenNKPandNKIandZKD->addOutput(zKd);
  FuzzyRule *fuzzypidRule1 = new FuzzyRule(1, ifENandDEN, thenNKPandNKIandZKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule1);

  // Building FuzzyRule 2
  FuzzyRuleAntecedent *ifENandDEZ = new FuzzyRuleAntecedent();
  ifENandDEZ->joinWithAND(nE, zdE);
  FuzzyRuleConsequent *thenNKPandNKIandPKD = new FuzzyRuleConsequent();
  thenNKPandNKIandPKD->addOutput(nKp);
  thenNKPandNKIandPKD->addOutput(nKi);
  thenNKPandNKIandPKD->addOutput(pKd);
  FuzzyRule *fuzzypidRule2 = new FuzzyRule(2, ifENandDEZ, thenNKPandNKIandPKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule2);

  // Building FuzzyRule 3
  FuzzyRuleAntecedent *ifENandDEP = new FuzzyRuleAntecedent();
  ifENandDEP->joinWithAND(nE, pdE);
  FuzzyRuleConsequent *thenZKPandZKIandPKD = new FuzzyRuleConsequent();
  thenZKPandZKIandPKD->addOutput(zKp);
  thenZKPandZKIandPKD->addOutput(zKi);
  thenZKPandZKIandPKD->addOutput(pKd);
  FuzzyRule *fuzzypidRule3 = new FuzzyRule(3, ifENandDEP, thenZKPandZKIandPKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule3);

  // Building FuzzyRule 4
  FuzzyRuleAntecedent *ifEZandDEN = new FuzzyRuleAntecedent();
  ifEZandDEN->joinWithAND(zE, ndE);
  FuzzyRuleConsequent *thenZKPandNKIandPKD = new FuzzyRuleConsequent();
  thenZKPandNKIandPKD->addOutput(zKp);
  thenZKPandNKIandPKD->addOutput(nKi);
  thenZKPandNKIandPKD->addOutput(pKd);
  FuzzyRule *fuzzypidRule4 = new FuzzyRule(4, ifEZandDEN, thenZKPandNKIandPKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule4);

  // Building FuzzyRule 5
  FuzzyRuleAntecedent *ifEZandDEZ = new FuzzyRuleAntecedent();
  ifEZandDEZ->joinWithAND(zE, zdE);
  FuzzyRuleConsequent *thenZKPandZKIandZKD = new FuzzyRuleConsequent();
  thenZKPandZKIandZKD->addOutput(zKp);
  thenZKPandZKIandZKD->addOutput(zKi);
  thenZKPandZKIandZKD->addOutput(zKd);
  FuzzyRule *fuzzypidRule5 = new FuzzyRule(5, ifEZandDEZ, thenZKPandZKIandZKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule5);

  // Building FuzzyRule 6
  FuzzyRuleAntecedent *ifEZandDEP = new FuzzyRuleAntecedent();
  ifEZandDEP->joinWithAND(zE, pdE);
  FuzzyRuleConsequent *thenZKPandPKIandNKD = new FuzzyRuleConsequent();
  thenZKPandPKIandNKD->addOutput(zKp);
  thenZKPandPKIandNKD->addOutput(pKi);
  thenZKPandPKIandNKD->addOutput(nKd);
  FuzzyRule *fuzzypidRule6 = new FuzzyRule(6, ifEZandDEP, thenZKPandPKIandNKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule6);

  // Building FuzzyRule 7
  FuzzyRuleAntecedent *ifEPandDEN = new FuzzyRuleAntecedent();
  ifEPandDEN->joinWithAND(pE, ndE);
  FuzzyRuleConsequent *thenZKPandZKIanNPKD = new FuzzyRuleConsequent();
  thenZKPandZKIanNPKD->addOutput(zKp);
  thenZKPandZKIanNPKD->addOutput(zKi);
  thenZKPandZKIanNPKD->addOutput(nKd);
  FuzzyRule *fuzzypidRule7 = new FuzzyRule(7, ifEPandDEN, thenZKPandZKIanNPKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule7);

  // Building FuzzyRule 8
  FuzzyRuleAntecedent *ifEPandDEZ = new FuzzyRuleAntecedent();
  ifEPandDEZ->joinWithAND(pE, zdE);
  FuzzyRuleConsequent *thenPKPandPKIandNKD = new FuzzyRuleConsequent();
  thenPKPandPKIandNKD->addOutput(pKp);
  thenPKPandPKIandNKD->addOutput(pKi);
  thenPKPandPKIandNKD->addOutput(nKd);
  FuzzyRule *fuzzypidRule8 = new FuzzyRule(8, ifEPandDEZ, thenPKPandPKIandNKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule8);

  // Building FuzzyRule 9
  FuzzyRuleAntecedent *ifEPandDEP = new FuzzyRuleAntecedent();
  ifEPandDEP->joinWithAND(pE, pdE);
  FuzzyRuleConsequent *thenPKPandPKIandZKD = new FuzzyRuleConsequent();
  thenPKPandPKIandZKD->addOutput(pKp);
  thenPKPandPKIandZKD->addOutput(pKi);
  thenPKPandPKIandZKD->addOutput(zKd);
  FuzzyRule *fuzzypidRule9 = new FuzzyRule(9, ifEPandDEP, thenPKPandPKIandZKD);
  press_fuzzypid->addFuzzyRule(fuzzypidRule9);
}
