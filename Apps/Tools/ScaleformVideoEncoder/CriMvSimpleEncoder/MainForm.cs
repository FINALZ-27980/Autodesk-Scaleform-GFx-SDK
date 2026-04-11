using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using CriMvEncoderControl;
using CriMvSimpleEncoder.Properties;

namespace CriMvSimpleEncoder
{
	public class MainForm : Form
	{
		private IContainer components;

		private ParametersSettingPanel encodeParamControl;

		private PictureBox picScaleformLogo;

		private PictureBox pictureBox1;

		private CriMovieEncoder encoder;

		protected override void Dispose(bool disposing)
		{
			if (disposing && components != null)
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CriMvSimpleEncoder.MainForm));
			this.encodeParamControl = new CriMvEncoderControl.ParametersSettingPanel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.picScaleformLogo = new System.Windows.Forms.PictureBox();
			((System.ComponentModel.ISupportInitialize)this.pictureBox1).BeginInit();
			((System.ComponentModel.ISupportInitialize)this.picScaleformLogo).BeginInit();
			base.SuspendLayout();
			this.encodeParamControl.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right;
			this.encodeParamControl.Location = new System.Drawing.Point(0, 65);
			this.encodeParamControl.Name = "encodeParamControl";
			this.encodeParamControl.Size = new System.Drawing.Size(825, 568);
			this.encodeParamControl.TabIndex = 0;
			this.pictureBox1.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right;
			this.pictureBox1.BackColor = System.Drawing.Color.Black;
			this.pictureBox1.ErrorImage = null;
			this.pictureBox1.Image = CriMvSimpleEncoder.Properties.Resources.sfheader2;
			this.pictureBox1.InitialImage = null;
			this.pictureBox1.Location = new System.Drawing.Point(751, 1);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(74, 58);
			this.pictureBox1.TabIndex = 2;
			this.pictureBox1.TabStop = false;
			this.picScaleformLogo.BackColor = System.Drawing.Color.Black;
			this.picScaleformLogo.Dock = System.Windows.Forms.DockStyle.Top;
			this.picScaleformLogo.ErrorImage = null;
			this.picScaleformLogo.Image = CriMvSimpleEncoder.Properties.Resources.sfheader1;
			this.picScaleformLogo.InitialImage = (System.Drawing.Image)resources.GetObject("picScaleformLogo.InitialImage");
			this.picScaleformLogo.Location = new System.Drawing.Point(0, 0);
			this.picScaleformLogo.Margin = new System.Windows.Forms.Padding(0);
			this.picScaleformLogo.MinimumSize = new System.Drawing.Size(0, 59);
			this.picScaleformLogo.Name = "picScaleformLogo";
			this.picScaleformLogo.Size = new System.Drawing.Size(825, 59);
			this.picScaleformLogo.TabIndex = 1;
			this.picScaleformLogo.TabStop = false;
			base.ClientSize = new System.Drawing.Size(825, 631);
			base.Controls.Add(this.pictureBox1);
			base.Controls.Add(this.picScaleformLogo);
			base.Controls.Add(this.encodeParamControl);
			this.MinimumSize = new System.Drawing.Size(800, 600);
			base.Name = "MainForm";
			this.Text = "Scaleform Video Encoder v3.0 Alpha";
			base.Load += new System.EventHandler(MainForm_Load);
			((System.ComponentModel.ISupportInitialize)this.pictureBox1).EndInit();
			((System.ComponentModel.ISupportInitialize)this.picScaleformLogo).EndInit();
			base.ResumeLayout(false);
		}

		public MainForm(CriMovieEncoder encoder, string appName, string versionNumber)
		{
			InitializeComponent();
			this.encoder = encoder;
			Text = appName + " " + versionNumber;
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			linkEventsBetweenEncoderAndGUI();
		}

		private void linkEventsBetweenEncoderAndGUI()
		{
			encodeParamControl.EncodingRequestedEvent += mainForm_EncodingRequested;
			encodeParamControl.CancelRequestedEvent += mainForm_CancelEncodingRequested;
			encodeParamControl.PreviewRequestedEvent += mainForm_PreviewRequested;
			encodeParamControl.LoadRequestedEvent += mainForm_LoadRequested;
			encoder.EncodingExited += encodeParamControl.EncodingExited;
			encoder.EncodingDataReceived += encodeParamControl.AppendEncodingLogReceived;
			encoder.EncodingErrorReceived += encodeParamControl.AppendEncodingErrorReceived;
			encoder.EncodingProgressChenged += encodeParamControl.EncodingProgressChanged;
		}

		private void mainForm_EncodingRequested(object sender, ParametersSettingPanel.EncodingRequestedEventArgs e)
		{
			encoder.StartEncode(e.EnvParam);
		}

		private void mainForm_CancelEncodingRequested(object sender, EventArgs e)
		{
			encoder.CancelEncode();
		}

		private void mainForm_PreviewRequested(object sender, ParametersSettingPanel.PreviewRequestedEventArgs e)
		{
			encoder.Preview(e.FileName, e.ExtendedPlayer);
		}

		private void mainForm_LoadRequested(object sender, ParametersSettingPanel.LoadRequestedEventArgs e)
		{
			encoder.Load(e.FileName);
		}

		private void encodeParamControl_Load(object sender, EventArgs e)
		{
		}
	}
}
