#include <Fuzzy.h>
// Fuzzy
Fuzzy *fuzzy_SR = new Fuzzy();

// FuzzyInput
FuzzySet *lowa = new FuzzySet(50, 50, 50, 55);
FuzzySet *mida = new FuzzySet(50, 60, 90, 100);
FuzzySet *higha = new FuzzySet(95, 100, 100, 100);

// FuzzyOutput
FuzzySet *lowb = new FuzzySet(60, 65, 85, 90);
FuzzySet *midb = new FuzzySet(85, 90, 90, 95);
FuzzySet *highb = new FuzzySet(90, 95, 105, 110);

void fuzzySRSetup()
{
  // FuzzyInput
  FuzzyInput *pwma = new FuzzyInput(1);

  pwma->addFuzzySet(lowa);
  pwma->addFuzzySet(mida);
  pwma->addFuzzySet(higha);
  fuzzy_SR->addFuzzyInput(pwma);

  // FuzzyOutput
  FuzzyOutput *pwmb = new FuzzyOutput(1);
    
  pwmb->addFuzzySet(lowb);
  pwmb->addFuzzySet(midb);
  pwmb->addFuzzySet(highb);
  fuzzy_SR->addFuzzyOutput(pwmb);

  // Building FuzzyRule "IF pwma = low THEN pwmb = high"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifALow = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifALow->joinSingle(lowa);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenBHigh = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenBHigh->addOutput(highb);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifALow, thenBHigh);
  // Including the FuzzyRule into Fuzzy
  fuzzy_SR->addFuzzyRule(fuzzyRule01);

  // Building FuzzyRule "IF pwma = mid THEN pwmb = mid"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifAMid = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifAMid->joinSingle(mida);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenBMid = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenBMid->addOutput(midb);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifAMid, thenBMid);
  // Including the FuzzyRule into Fuzzy
  fuzzy_SR->addFuzzyRule(fuzzyRule02);

  // Building FuzzyRule "IF pwma = high THEN pwmb = low"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifAHigh = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifAHigh->joinSingle(higha);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenBLow = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenBLow->addOutput(lowb);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifAHigh, thenBLow);
  // Including the FuzzyRule into Fuzzy
  fuzzy_SR->addFuzzyRule(fuzzyRule03);
}
