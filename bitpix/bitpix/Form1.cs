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
    public struct setingBit
    {
        public bool leftBitsAlign;
        public bool emptyBits;
    }
    public partial class Form1 : Form
    {
        static string pathImageStr;
        static Bitmap holst;
        public static setingBit setBits;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            pictureBox1.Load("start.png");
            pathImageStr = "";
            label2.Text = "";
            label3.Text = "";
            setBits.emptyBits = true;
            setBits.leftBitsAlign = true;
            
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Author Dus Oleg\nmail 2andnot@gmail.com\nCreated on 09/09/2017\nSupported bitmap formats", "BitPix v1.0", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            pathImageStr = openFileDialog1.FileName;

            if (holst != null)
            {
                holst.Dispose();
            }

            holst = new Bitmap(pathImageStr);
            
            if (holst.Width <= pictureBox1.Width && holst.Height <= pictureBox1.Height)
            {
                label2.Text = pathImageStr;
                pictureBox1.ImageLocation = pathImageStr;
                label3.Text = "Width = " + holst.Width.ToString() + " Height = " + holst.Height.ToString();
            }
            else
            {
                pathImageStr = "";
                holst.Dispose();
                MessageBox.Show("This picture is too lots of size\nPlease select a picture with\na width of 0 ... 320px and a height of 0 ... 240px", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (pathImageStr != "")
            {
                int bitLen = holst.Width * holst.Height;

                //int arrLen = ((holst.Width / 8) + (holst.Width % 8 == 0 ? 0 : 1)) * holst.Height;
                string emptyBits = "";
                if (setBits.emptyBits)
                {
                    int emptyLen = (holst.Width % 8);
                    emptyLen = emptyLen == 0 ? 8 : emptyLen;
                    for (int z = 0; z < 8 - emptyLen; z++)
                    {
                        emptyBits += "0";
                    }
                }
                else
                {
                    int emptyLen = (bitLen % 8);
                    emptyLen = emptyLen == 0 ? 8 : emptyLen;
                    for (int z = 0; z < 8 - emptyLen; z++)
                    {
                        emptyBits += "0";
                    }
                }

                int _X, _Y;
                int countArr = 0;
                Color colBuff;
                string res = "";
                string buff = "";
                buff += "unsigned char " + (textBox2.Text.Length !=0 ? textBox2.Text : "NoNameArray")+ "[]=\n{\n";
                for (int i = 0; i < bitLen; i++)
                {
                    _X = i >= holst.Width ? (i % holst.Width) : i;
                    _Y = i / holst.Width;
                    colBuff = holst.GetPixel(_X, _Y);

                    if (!setBits.emptyBits && !setBits.leftBitsAlign && i == 0)
                    {
                        res = emptyBits;
                    }

                    if (res.Length < 8)
                    {
                        if (colBuff.B == 0 && colBuff.G == 0 && colBuff.R == 0)
                        {
                            res += "1";
                        }
                        else
                        {
                            res += "0";
                        }
                    }
                    else
                    {
                        buff += "B" + res + ",\n";
                        countArr++;
                        res = "";
                        if (colBuff.B == 0 && colBuff.G == 0 && colBuff.R == 0)
                        {
                            res += "1";
                        }
                        else
                        {
                            res += "0";
                        }
                    }


                    if (setBits.emptyBits && setBits.leftBitsAlign && _X == holst.Width - 1)
                    {
                        buff += "B" + res + emptyBits + ",\n";
                        countArr++;
                        res = "";
                    }
                    else if (setBits.emptyBits && !setBits.leftBitsAlign && _X == 8 - emptyBits.Length-1)
                    {
                        
                        buff += "B" + emptyBits + res + ",\n";
                        countArr++;
                        res = "";
                    }
                    else if (setBits.emptyBits && _X == holst.Width - 1)
                    {
                        buff += "B" + res + ",\n";
                        countArr++;
                        res = "";
                    }

                    if (!setBits.emptyBits && setBits.leftBitsAlign && i == bitLen-1)
                    {
                        buff +=  "B" + res + emptyBits +"  ";
                        countArr++;
                    }else if (!setBits.emptyBits && i == bitLen-1)
                    {
                        buff += "B" + res + "  ";
                        countArr++;
                    }



                }
                textBox1.Text = buff.Remove(buff.Length - 2) + "\n};\n//" + (countArr).ToString()+" elements";
            }
        }

        private void setingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 exm = new Form2();
            exm.Show();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form3 help = new Form3();
            help.Show();
        }
    }
}
