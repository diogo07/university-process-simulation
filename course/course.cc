#include <string.h>
#include <omnetpp.h>
#include <math.h>
using namespace omnetpp;

class Period : public cSimpleModule {
  private:
    double evaluation = 0.0;
    int disapprovals = 0;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateDisplay();

  public:
    void randomEvaluation(){
        double f = (double)rand() / RAND_MAX;
        evaluation = f * (100.0);
    };
};

Define_Module(Period);


void Period::updateDisplay() {
    const char* txt2 = "off";
    const char* color = "red";
    const char* status = "status/red";
    const char* msgRep = std::to_string(disapprovals).c_str();

    if (evaluation >= 70.0) {
        color = "green";
        status = "status/green";
    }
    cDisplayString& ds = getDisplayString();
    ds.setTagArg("i2", 0, status);
    ds.setTagArg("i", 1, color);
    refreshDisplay();
    bubble(msgRep);
}

void Period::initialize() {
    randomEvaluation();
    if (getIndex() == 0) {

       disapprovals = 0;

       if (evaluation >= 70.0){
           updateDisplay();
           cMessage *msg = new cMessage("Discente");
           send(msg, "out", 0);
       } else {
           updateDisplay();
           cMessage *msg = new cMessage("Discente");
           send(msg, "out", 1);
       }

    }
}

void Period::handleMessage(cMessage *msg) {
    randomEvaluation();
    disapprovals += 1;
    if (evaluation >= 70.0) {
        send(msg, "out", 0);
        updateDisplay();
    } else {
        send(msg, "out", 1);
        updateDisplay();
    }


}
