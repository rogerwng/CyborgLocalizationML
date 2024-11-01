# Undergraduate Research at the University of Osaka Japan
This is a subset of my research project done in the Summer 2023 term while I was an undergraduate researcher at the University of Osaka. As a member of LiveMechX Lab led by Professor Morishima Keisuke, I worked on many projects including the cyborg insect Urban Search and Rescue platform.  

This project involved artificially enhanced cockroaches designed to automatically search for human survivors in disaster areas, particularly in dangerous environments that human operators cannot access.  

A huge issue with these systems is localization - the ability for operators to track and locate the robotic platforms during operation. Since the insects cannot carry heavy GPS devices nor can the attached microprocessor support such power intensive modules, a different approach is needed to accurately assess the position of the system once it has located a human survivor.  

My contribution is an analysis of various machine learning models (regression trees) in predicting and transmitting the systems location based on data colleted from an onboard inertial measurement unit (IMU). With a best accuracy of about 0.75 on extremely limited experimental data, regression tree models may be an effective and efficient manner of localization.  

Please read the attached research paper which details my experiments and procedure.  

EDIT: Looking back at this project in 2024, I'd like to point out that the scores computed by all models were in the format of Mean Squared Error, instead of Accuracy. I'd love to go back and work through the dataset to reevaluate my methods.
