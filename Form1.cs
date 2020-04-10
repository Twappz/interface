using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Diagnostics;
using System.Security;

namespace Interface
{
    public partial class Form1 : Form
    {

        private SerialPort myport;
        private DateTime datetime;
        private string in_data;
        bool isConnected = false;
        String[] ports;
        String hex;
        // SerialPort port;

        public Form1()
        {
            InitializeComponent();
            getAvailableComPorts();
            button5.Enabled = false;


            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
                Console.WriteLine(port);
                if (ports[0] != null)
                {
                    // comboBox1.Text = "--Select--";
                    comboBox1.SelectedItem = ports[0];
                }
            }
        }

        private void getAvailableComPorts()
        {
            comboBox1.Items.Clear();
            ports = SerialPort.GetPortNames();
        }

        
        private void checkboxes()
        {
            //throw new NotImplementedException();
            if (tech_tb.Text == "" || wo_tb.Text == "" || sn_tb.Text == "" || pn_tb.Text == "")
            {
                MessageBox.Show("Please fill out the UUT details");
            }

            else
            {

                string selectedPort = comboBox1.GetItemText(comboBox1.SelectedItem);
                myport = new SerialPort(selectedPort);
                myport.BaudRate = 9600;
                //myport.PortName = port_name_tb.Text;
                //myport.StopBits = StopBits.Two;
                myport.Parity = Parity.None;
                myport.DataBits = 8;
                // myport.StopBits = StopBits.None;
                myport.DataReceived += myport_DataReceived;
                myport.Handshake = Handshake.None;
                bool isConnected = true;
                button5.Enabled = true;
               // myport.ReadTimeout = 10000;


            }
        }

        void myport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
        
            in_data = myport.ReadLine();
            this.Invoke(new EventHandler(displaydata_event));

        }

        private void displaydata_event(object sender, EventArgs e)
        {
            datetime = DateTime.Now;
            string time = datetime.Hour + ":" + datetime.Minute + ":" + datetime.Second;
            // data_tb.AppendText(time + "\t\t" + in_data+"\n");
            data_tb.AppendText(in_data + "\n\n");
            //int data_value = Convert.ToInt32(in_data);
            //value_pb.Value = data_value;

            if (in_data.Contains("Starting"))
            {
                string box_msg = "Push S1 on the UUT to ON and click OK to continue";
                string box_title = "S1 ON Test";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#STAR\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }

            if (in_data.Contains("S1 ON test completed"))
            {
                string box_msg = "Push S1 on the UUT to OFF and click OK to continue";
                string box_title = "S1 OFF TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON1\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }


           else if (in_data.Contains("S1 OFF Test completed"))
            {
                string box_msg = "Push S2 on the UUT to ON and click OK to continue";
                string box_title = "S2 ON TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON2\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }

           else if (in_data.Contains("S2 ON test completed"))
            {
                string box_msg = "Push S2 on the UUT to OFF and click OK to continue";
                string box_title = "S2 OFF TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON3\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }

           else if (in_data.Contains("S2 OFF test completed"))
            {
                string box_msg = "Push S3 on the UUT to ON and click OK to continue";
                string box_title = "S3 ON TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON4\n");
                }  
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }

           else if (in_data.Contains("S3 ON test completed"))
            {
                string box_msg = "Push S3 on the UUT to OFF and click OK to continue";
                string box_title = "S3 OFF TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON5\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }


           else if (in_data.Contains("S3 OFF test completed"))
            {
                string box_msg = "Push S4 on the UUT to ON and click OK to continue";
                string box_title = "S4 ON TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON6\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }

           else if (in_data.Contains("S4 ON test completed"))
            {
                string box_msg = "Push S4 on the UUT to OFF and click OK to continue";
                string box_title = "S4 OFF TEST";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#CON7\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                } 
            }

            else if (in_data.Contains("S4 OFF test completed"))
            {
                string box_msg = "Connect a +28VDC to the manual breakout box" +
                                  "ABI 1309C at jack B-3(J2-3). Connect the negative " +
                                  "to the 28VDC(-) terminal at the back of the tester." +
                                  "Click OK to continue the test";
                string box_title = "PB Lamp Test";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.OKCancel);
                if (result == DialogResult.OK)
                {
                    myport.Write("#SOLN\n");
                }
                else if (result == DialogResult.Cancel)
                {
                    myport.Write("");
                }
            }


            else if (in_data.Contains("Verifying J2-10..."))
            {
                string box_msg = "Verify S1 INOP light illuminates"; //Verify S1 INOP is ON?
                string box_title = "S1 Lamp Test";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    myport.Write("#210P\n"); //Show  message that it passes.
                  
                }
                else if (result == DialogResult.No)
                {
                 data_tb.AppendText("S1 Lamp Test......................................FAILED");
                }
                  myport.Write("#0J24\n");  //Proceed to next pin to test
            }


            else if (in_data.Contains("Verifying J2-4...")) // J2-4 Test completed?
            {
                string box_msg = "Verify S3 and S1 INOP light illuminates";
                string box_title = "S3 Lamp Test";
                DialogResult result = MessageBox.Show(box_msg, box_title, MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    myport.Write("#240P\n");//Show  message that it passes.

                }
                else if (result == DialogResult.No)
                {
                    data_tb.AppendText("S3 Lamp Test......................................FAILED");
                }
                 myport.Write("");
            }



        }

        private void stop_btn_Click(object sender, EventArgs e)
        {

            if (isConnected)
            {
                //isConnected = true;
                //myport.Write("#STAR\n");

                // connectToArduino();
            }
            else
            {
                //disconnectFromArduino();
            }

            try
            {
                myport.Close();
            }
            catch (Exception ex2)
            {
                MessageBox.Show(ex2.Message, "Error");
            }
        }
        
        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void Restart()
        {
            throw new NotImplementedException();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void start_btn_Click_1(object sender, EventArgs e)
        {

            //checkboxes();
            //myport.Open();
            //data_tb.Text = "";

            try
            {
               checkboxes();
               myport.Open();
               //data_tb.Text = "";

            }
            catch (Exception ex)
            {
                // MessageBox.Show(ex.Message, "Error");
                // MessageBox.Show("Interface Box is offline");

            }

        }

        private void save_btn_Click_1(object sender, EventArgs e)
        {
            if (tech_tb.Text == "" || wo_tb.Text == "" || sn_tb.Text == "" || pn_tb.Text == "")
            {
                MessageBox.Show("Please fill out the details of the UUT");

            }

            else
            try
            {
                string time = datetime.Hour + ":" + datetime.Minute + ":" + datetime.Second;
                string pathfile = @"C:\DATA\";
                string filename = wo_tb.Text + "_" + tech_tb.Text + "_" + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + ".txt";
                System.IO.File.WriteAllText(pathfile + filename,"QC:"+textBox1.Text + "\t\t"+"Tech:" + tech_tb.Text + "\t\t" + "Work Order:" + wo_tb.Text + "\t\t" + "Part Number:" + pn_tb.Text + "\t\t" + "Serial No.:" + sn_tb.Text + "\n\n\n\n\n\n" + data_tb.Text);
                MessageBox.Show("Data has been saved to " + pathfile, "Save File");
            }

            catch (Exception ex3)
            {
                MessageBox.Show(ex3.Message, "Error");
            }

        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Text Files (*.txt)|*.txt" + "|" +
                               "Image Files (*.png;*.jpg)|*.png;*.jpg" + "|" +
                               "All Files (*.*)|*.*";
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                try
                {
                    string file = openFileDialog1.FileName;
                    using (System.IO.FileStream fs = File.Open(file, FileMode.Open)) ;
                    {
                        Process.Start("notepad.exe", file);
                    }
                }
                catch (SecurityException ex)
                {

                    MessageBox.Show($"Security error.\n\nError message: {ex.Message}\n\n" +
                $"Details:\n\n{ex.StackTrace}");

                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
          
                if (myport.IsOpen)
                {
                //Send text to port
                //myport.WriteLine("" + Environment.NewLine);
                //txtMessage.Clear();
                // myport.WriteLine("");
                data_tb.Clear();
               myport.Write("#INIT\n");
                    
                }

          
            if (tech_tb.Text == "" || wo_tb.Text == "" || sn_tb.Text == "" || pn_tb.Text == "")
            {
                MessageBox.Show("Please fill out the details of the UUT");

            }
           

        }

        private void stop_button_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            getAvailableComPorts();

            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
                Console.WriteLine(port);
                if (ports[0] != null)
                {
                    // comboBox1.Text = "--Select--";
                    comboBox1.SelectedItem = ports[0];
                }
            }
        }
                  
        private void button4_Click(object sender, EventArgs e)
          
        {
            if (string.IsNullOrEmpty(comboBox2.Text))
                {
                MessageBox.Show("Select a task or part number");
                }

            else
                {

                var processStartInfo = new ProcessStartInfo();
               // processStartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;

                processStartInfo.WorkingDirectory = @"c:\\ate\\";

                processStartInfo.FileName = "cmd.exe";

                //processStartInfo.Arguments = "/C ArduinoSketchUploader.exe --file=C:\\Ate\\ATE_BOX_ohm.ino.hex --model=UnoR3";
                processStartInfo.Arguments = hex;
                Process proc = Process.Start(processStartInfo);
               }
            }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            switch (comboBox2.SelectedItem.ToString().Trim())
            {
                    case "69-55179-78":
                    hex= "/C Upload.exe --file=C:\\Ate\\Hex\\ATE_BOX_ohm.ino.hex --model=UnoR3";
                    wo_tb.Clear();
                    sn_tb.Clear();
                    textBox1.Text = "3214";
                    status.Text = "FSIM Test in Progress...";
                    pn_tb.Text = "69-55179-78";
                    break;

                case "69-55179-78 Mod A":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\ATE_BOX_ohm_AUG_18_19.ino.hex --model=UnoR3";
                    textBox1.Text = "3214A";
                    wo_tb.Clear();
                    sn_tb.Clear();
                    pn_tb.Text = "69-55179-78 Mod A";
                    status.Text = "FSIM Test in Progress...";
                    break;

                case "P1-Self Test":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\P1.ino.hex --model=UnoR3";
                    textBox1.Text = "SELF TEST";
                    pn_tb.Text = "SELF TEST";
                    wo_tb.Text = "NA";
                    sn_tb.Text = "NA";
                    status.Text = "P1 Self Test...";
                    MessageBox.Show(" Please connect a 5000 ohms decade resistor box \n" +
                                    " at the output jacks. Close this window and \n" +
                                    " RUN the self test when ready.");
                    break;

                case "P2-Self Test":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\P2.ino.hex --model=UnoR3";
                    textBox1.Text = "SELF TEST";
                    pn_tb.Text = "SELF TEST";
                    wo_tb.Text = "NA";
                    sn_tb.Text = "NA";
                    status.Text = "P2 Self Test...";
                    MessageBox.Show(" Please connect a 5000 ohms decade resistor box \n" +
                                    " at the output jacks. Close this window and \n" +
                                    " RUN the self test when ready.");
                    break;

                case "P3-Self Test":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\P3.ino.hex --model=UnoR3";
                    textBox1.Text = "SELF TEST";
                    pn_tb.Text = "SELF TEST";
                    wo_tb.Text = "NA";
                    sn_tb.Text = "NA";
                    status.Text = "P3 Self Test...";
                    MessageBox.Show(" Please connect a 5000 ohms decade resistor box \n" +
                                    " at the output jacks. Close this window and \n" +
                                    " RUN the self test when ready.");
                    break;

                case "Board Test":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\testboard2.ino.hex --model=UnoR3";
                    wo_tb.Text="Test";
                    sn_tb.Text="Test";
                    textBox1.Text = "Test";
                    status.Text = "Board Test in Progress...";
                    pn_tb.Text = "Test";
                    tech_tb.Text="Test";
                    break;

                case "233N3212-11":
                    hex = "/C Upload.exe --file=C:\\Ate\\Hex\\233N3212.ino.hex --model=UnoR3";
                    textBox1.Text = "3380";
                    pn_tb.Text = "233N3212";
                    wo_tb.Text = "NA";
                    sn_tb.Text = "NA";
                    status.Text = "Testing P/N 233N3212-11";
                    break;

                default:
                    MessageBox.Show("P/N NOT FOUND!");
                    break;
               
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            try
            {
                if (myport.IsOpen)
                {
                    data_tb.Clear();
                    myport.Write("#RESE\n");
                    // myport.DtrEnable = true;
                }
               
            }
            catch (Exception ex)

            {
                
                    MessageBox.Show("Port is not connected! ");
            }
            
        }

        private void about_btn_Click(object sender, EventArgs e)
        {
            MessageBox.Show(" TEST INTERFACE BETA RELEASE \n\n" +
                           " This program is free software; you can redistribute it \n" +
                           " under the terms of the GNU General Public License as published by \n" +
                           " the Free Software Foundation; either version 2 of the License, or \n" +
                           " any later version. \n" +

                            " This program is distributed in the hope that it will be useful,\n " +
                            " but WITHOUT ANY WARRANTY; without even the implied warranty of \n " +
                            " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n " +
                            " See the GNU General Public License for more details.\n " +
                            " email rontab68@gmail.com for technical support questions");
        }

        private void data_tb_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void groupBox5_Enter(object sender, EventArgs e)
        {

        }
    }
}
    
    




