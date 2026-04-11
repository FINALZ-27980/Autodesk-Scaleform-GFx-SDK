using System;
using System.Windows.Forms;

namespace CriMvSimpleEncoder
{
	internal static class Program
	{
		private const string appName = "Scaleform Video Encoder";

		private const string versionNumber = "v4.0";

		private const string consoleEncoderPath = "medianoche.exe";

		private const string videoPlayerPath = "GFxMediaPlayer.exe";

		private const string videoPlayerSwfPath = "VideoPlayer.swf";

		public static void ShowErrorMessage(string msg, bool isError)
		{
			string caption = "Scaleform Video Encoder : Error";
			MessageBoxIcon icon = (isError ? MessageBoxIcon.Hand : MessageBoxIcon.Exclamation);
			MessageBox.Show(msg, caption, MessageBoxButtons.OK, icon);
		}

		[STAThread]
		private static void Main()
		{
			CriMovieEncoder encoder = new CriMovieEncoder("medianoche.exe", "GFxMediaPlayer.exe", "VideoPlayer.swf", "Scaleform Video Encoder");
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MainForm(encoder, "Scaleform Video Encoder", "v4.0"));
		}
	}
}
