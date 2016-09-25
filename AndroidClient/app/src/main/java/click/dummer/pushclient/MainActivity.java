package click.dummer.pushclient;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {
    private FeedAdapter feedAdapter;
    private ListView feedList;

    static {
        System.loadLibrary("ClientWrapper");
    }

    private native int answer();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        feedAdapter = new FeedAdapter(this);
        feedList = (ListView) findViewById(R.id.feedList);
        feedList.setAdapter(feedAdapter);
    }

    public void sendMsg(View view) {
        EditText editText = (EditText) findViewById(R.id.editText);
        Feed f = new Feed();
        f.title = Integer.toString(answer());
        f.body = editText.getText().toString();
        feedAdapter.addItem(f);
    }
}
