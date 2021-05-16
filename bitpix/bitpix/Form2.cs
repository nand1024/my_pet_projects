using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace bitpix
{
    public partial class Form2 : Form
    {
        string lefemp, lefmin, rigemp, rigmin;
        public Form2()
        {
            InitializeComponent();
        }

        private void reloadSet()
        {
            if (checkBox1.Checked)
            {
                if (radioButton1.Checked)
                {
                    textBox1.Text = lefemp;
                }
                else
                {
                    textBox1.Text = rigemp;
                }
            }
            else
            {
                if (radioButton1.Checked)
                {
                    textBox1.Text = lefmin;
                }
                else
                {
                    textBox1.Text = rigmin;
                }
            }
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {
            lefemp = "b10101000 \nb00101000 \nb11101000 \nb00001000 \nb11111000";
            lefmin = "b10101001 \nb01111010 \nb00011111 \nb10000000";
            rigemp = "b00010101 \nb00000101 \nb00011101 \nb00000001 \nb00011111";
            rigmin = "b00000001 \nb01010010 \nb11110100 \nb00111111";
            if (Form1.setBits.leftBitsAlign)
            {
                radioButton1.Checked = true;
            }
            else
            {
                radioButton2.Checked = true;
            }
                checkBox1.Checked = Form1.setBits.emptyBits;
            pictureBox1.Load("set_examlpe.png");
            reloadSet();
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            reloadSet();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            reloadSet();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            reloadSet();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1.setBits.emptyBits = checkBox1.Checked;
            Form1.setBits.leftBitsAlign = radioButton1.Checked;
            this.Close();
        }
    }
}
