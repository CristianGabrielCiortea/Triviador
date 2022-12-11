#pragma once
#include <QWidget>
#include <QTimer>
#include <QRandomGenerator>
#include <QDoubleValidator>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include "ui_QuestionWindow.h"

#include <variant>
#include <string>
#include <cpr/cpr.h>
#include <crow.h>

enum class QuestionType
{
    MultipleAnswer,
    NumericalAnswer
};

class QuestionWindow : public QWidget
{
    Q_OBJECT

public:
    QuestionWindow(QWidget* parent = nullptr);
    ~QuestionWindow();

    // Setters
    void SetQuestion(const std::string& question);
    void SetAnswer(int position, const std::string& answer);
    void SetRightAnswer(const std::string& answer);
    void SetRightAnswer(const int& answer);
    void SetQuestionType(const QuestionType& type);
    
    // Getters
    void FetchQuestion();
    void FetchMultipleAnswerQuestion();
    void FetchNumericalAnswerQuestion();
    
    // Other
    void Show();
    void StartTimer();

private slots:
    void on_hammerButton_clicked();
    void on_telescopeButton_clicked();
    void on_parrotButton_clicked();
    
    void UpdateProgressBar();

private:
    // Setters
    void SetShadowEffect();
    void SetTimer();
    
private:
    // Constants
    static const int kAnswerCount = 4;
    
    // UI
    Ui::QuestionWindowClass ui;
    std::array<QPushButton*, kAnswerCount> ui_answers;
    
    QTimer* m_timer;
    QuestionType m_type;
    std::variant<std::string, int> m_rightAnswer;
};
